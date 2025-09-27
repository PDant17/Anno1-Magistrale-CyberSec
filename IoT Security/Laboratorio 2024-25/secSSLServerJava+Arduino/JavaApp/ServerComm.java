import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.security.SecureRandom;
import java.util.Objects;

import javax.net.ssl.KeyManagerFactory;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLServerSocket;
import javax.net.ssl.SSLServerSocketFactory;
import javax.net.ssl.TrustManagerFactory;

public class ServerComm extends Thread {
	private String address;
	private String port;
	private ServerSocket serverSocket;
	private boolean useSSL;
	private String tlsVersion, trustStoreName, trustStorePassword, keyStoreName, keyStorePassword;
	
	public ServerComm(String address, String port, boolean useSSL) {
		super();
		this.address = address;
		this.port = port;
		this.useSSL = useSSL;
	}
	
	public void configureSSL(String tlsVersion, String trustStoreName,
			String trustStorePassword, String keyStoreName, String keyStorePassword) {
		this.tlsVersion = tlsVersion;
		this.trustStoreName = trustStoreName;
		this.trustStorePassword = trustStorePassword;
		this.keyStoreName = keyStoreName;
		this.keyStorePassword = keyStorePassword;
	}
	
	public String getAddress() {
		return address;
	}
	public String getPort() {
		return port;
	}
	
	public void run() {
		InetAddress addr;
		try {
			addr = InetAddress.getByName(address);
			int portInt = Integer.parseInt(port);
			if (portInt <= 0) {
			    throw new IllegalArgumentException(
			         "Port number cannot be less than or equal to 0");
			}
			if(useSSL) {
				try {
					Objects.requireNonNull(tlsVersion, "TLS version is mandatory");
					KeyStore trustStore = KeyStore.getInstance(KeyStore.getDefaultType());
					File tFile = new File(trustStoreName);
					if(!tFile.exists()) {
						System.err.println("TStore file not exists");
					}
					FileInputStream fTIn = new FileInputStream(tFile);
					trustStore.load(fTIn, trustStorePassword.toCharArray());
					fTIn.close();
				    TrustManagerFactory tmf = TrustManagerFactory
				        .getInstance(TrustManagerFactory.getDefaultAlgorithm());
				    tmf.init(trustStore);
	
				    KeyStore keyStore = KeyStore.getInstance(KeyStore.getDefaultType());
				    File kFile = new File(keyStoreName);
					if(!kFile.exists()) {
						System.err.println("KStore file not exists");
					}
					FileInputStream fKIn = new FileInputStream(kFile);
					keyStore.load(fKIn, trustStorePassword.toCharArray());
					fKIn.close();
				    KeyManagerFactory kmf = KeyManagerFactory
				        .getInstance(KeyManagerFactory.getDefaultAlgorithm());
				    kmf.init(keyStore, keyStorePassword.toCharArray());
				    SSLContext ctx = SSLContext.getInstance("TLS");
				    ctx.init(kmf.getKeyManagers(), tmf.getTrustManagers(),
				        SecureRandom.getInstanceStrong());
	
				    SSLServerSocketFactory factory = ctx.getServerSocketFactory();
				    System.out.println("Actived ServerSocket TLS on " + address + " port " + port);	
					try (ServerSocket listener = factory.createServerSocket(portInt, 10, addr); SSLServerSocket sslListener = (SSLServerSocket) listener;) {
					      sslListener.setNeedClientAuth(false);
					      sslListener.setEnabledProtocols(new String[] {tlsVersion});
					      while (true) {
					        try {
					        	Socket clientSocket = sslListener.accept();
					        	handleClient(clientSocket);	
					        } catch (Exception ex) {}
					      }
				    } 
				} catch (KeyStoreException e) { e.printStackTrace(); }
				catch (Exception e) { e.printStackTrace(); }
			} else {
				try {
					serverSocket = new ServerSocket(portInt, 10, addr);
					System.out.println("Actived ServerSocket on " + address + " port " + port);	
					while(!this.isInterrupted()) {
						try {
							Socket clientSocket = serverSocket.accept();
						    handleClient(clientSocket);	
						} catch (SocketException ex) {}
					} 
				} catch (NumberFormatException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} finally {
					try {
						serverSocket.close();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("Terminated ServerSocket on " + address + " port " + port);	
	}
	
	private void handleClient(Socket clientSocket) throws IOException {
		BufferedReader in = new BufferedReader(
	        new InputStreamReader(clientSocket.getInputStream()));
		PrintStream out = new PrintStream(clientSocket.getOutputStream());
		@SuppressWarnings("unused")
		Worker worker = new Worker(clientSocket.getInetAddress().getHostAddress(), in, out);
	}
	public void interruptMe() {
		if(!this.isInterrupted()) {
			this.interrupt();
			try {
				serverSocket.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}
