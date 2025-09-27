keytool -genkeypair -alias server -keyalg RSA -sigalg SHA256withRSA -keysize 2048 -keystore servercert.p12 -storetype pkcs12 -v -storepass abc123 -validity 10000 -ext 
san=ip:10.3.4.10
