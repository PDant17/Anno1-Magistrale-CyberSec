import os
import music21 as m21
import json
import numpy

from tensorflow import keras as keras

from music21 import environment


KERN_DATASET_PATH = "deutschl/erk"
SAVE_DIR = "dataset"
SINGLE_FILE_DATASET = "file_dataset"
MAPPING_PATH = "mapping.json"

SEQUENCE_LENGTH = 64

env = environment.Environment(forcePlatform='ubuntu')
env['musicxmlPath'] = '/usr/bin/mscore3'

ACCEPTABLE_DURATION = [
    0.25,
    0.5,
    0.75,
    1,
    1.5,
    2,
    3,
    4
]


def has_acceptable_durations(song, ACCEPTABLE_DURATION):
    for note in song.flat.notesAndRests:
        if note.duration.quarterLength not in ACCEPTABLE_DURATION:
            return False

    return True


def preprocess(dataset_path):
    pass

    # Load dataset
    print("Loading songs...")
    songs = load_songs_in_kern(dataset_path)
    print(f"Loaded {len(songs)} songs.")

    for i, song in enumerate(songs):

        # Filter durations
        if not has_acceptable_durations(song, ACCEPTABLE_DURATION):
            continue

        # Transpose Cmaj/Amin
        song = transpose(song)

        # Encoding melodies
        encoded_song = encode_song(song)

        # Save dataset file txt
        save_path = os.path.join(SAVE_DIR,str(i))
        with open(save_path,"w") as fp:
            fp.write(encoded_song)


def load_songs_in_kern(dataset_path):

    songs = []
    for path, subdirs, files in os.walk(dataset_path):
        for file in files:
            if file[-3:] == "krn":
                song = m21.converter.parse(os.path.join(path,file))
                songs.append(song)

    return songs


def transpose(song):
    parts = song.getElementsByClass(m21.stream.Part)
    measures_part0 = parts[0].getElementsByClass(m21.stream.Measure)
    key = measures_part0[0][4]

    if not isinstance(key,m21.key.Key):
        key = song.analyze("key")

    print(key)

    #interval = None
    if key.mode == "major":
       interval = m21.interval.Interval(key.tonic,m21.pitch.Pitch("C"))

    if key.mode == "minor":
       interval = m21.interval.Interval(key.tonic,m21.pitch.Pitch("A"))

    transposed_song = song.transpose(interval)

    return transposed_song


def encode_song(song,time_stemp=0.25):

    encode_song = []

    for event in song.flat.notesAndRests:

        if isinstance(event,m21.note.Note):
            symbol = event.pitch.midi #60

        if isinstance(event,m21.note.Rest):
            symbol = "r"

        steps = int(event.duration.quarterLength / time_stemp)

        for step in range(steps):
            if step == 0:
                encode_song.append(symbol)
            else:
                encode_song.append('_')

    encode_song = " ".join(map(str,encode_song))

    return encode_song


def load(file_path):
    with open(file_path,"r") as fp:
        song = fp.read()

    return song


def create_single_file_dataset(dataset_path, file_dataset_path, sequence_length):

    new_song_delimiter = "/ " * sequence_length

    songs = ""

    for path, _, files in os.walk(dataset_path):
        for file in files:
            file_path = os.path.join(path,file)
            song = load(file_path)

            songs = songs + song + new_song_delimiter


    songs = songs[:-1]

    with open(file_dataset_path,"w") as fp:
        fp.write(songs)

    return songs


def create_mapping(songs, mapping_path):

    mappings = {}

    songs = songs.split()
    vocabulary = list(set(songs))

    for i, symbol in enumerate(vocabulary):
        mappings[symbol] = i

    with open(mapping_path, "w") as fp:
        json.dump(mappings, fp, indent=4)


def convert_songs_to_int(songs):
    int_songs = []

    with open(MAPPING_PATH,"r") as fp:
        mappings = json.load(fp)

    songs = songs.split()

    for symbol in songs:
        int_songs.append(mappings[symbol])

    return int_songs


# [11, 30, 60, 12, 34, 66,...........]
# [11, 30] --> 60
# [30, 60] --> 12
# [60, 12] --> 34 .......
def generate_training_sequences(sequence_length):

    songs = load(SINGLE_FILE_DATASET)
    int_songs = convert_songs_to_int(songs)

    inputs = []
    targets = []

    num_sequences = len(int_songs) - sequence_length
    for i in range(num_sequences):
        inputs.append(int_songs[i:i+sequence_length])
        targets.append(int_songs[i+sequence_length])


   # [[0,1,2] [1,1,2]]










def main():
    preprocess(KERN_DATASET_PATH)
    songs = create_single_file_dataset(SAVE_DIR, SINGLE_FILE_DATASET, SEQUENCE_LENGTH)
    create_mapping(songs,MAPPING_PATH)




# MAIN
if __name__ == "__main__":
  main()










