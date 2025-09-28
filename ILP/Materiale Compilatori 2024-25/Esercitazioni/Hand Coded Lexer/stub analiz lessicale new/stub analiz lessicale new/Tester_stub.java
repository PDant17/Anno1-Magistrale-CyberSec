
public class Tester {

	public static void main(String[] args) {

		LexicalAnalyzer lexicalAnalyzer = new LexicalAnalyzer();
		String filePath = "file_input.txt";

		if (lexicalAnalyzer.initialize(filePath)) {

			Token token;
			try {
				while ((token = lexicalAnalyzer.nextToken()) != null) {
					System.out.println(token);
				}
			} catch (Exception e) {
				e.printStackTrace();
			}

		} else
			System.out.println("File not found!!");
	}

}
