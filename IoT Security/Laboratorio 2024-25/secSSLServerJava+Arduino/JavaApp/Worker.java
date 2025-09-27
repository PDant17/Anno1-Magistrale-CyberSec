import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintStream;
import java.io.StringReader;
import java.util.Optional;

import javax.net.ssl.SSLException;

import javax.net.ssl.SSLException;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.ErrorHandler;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

public class Worker extends Thread{
	private BufferedReader in;
	private PrintStream out;
	private String adr;

	public Worker(String adr, BufferedReader in, PrintStream out) {
		super();
		this.adr = adr;
		this.in = in;
		this.out = out;
		
		this.start();
	}
	
	class NullErrorHandler implements ErrorHandler {
	    @Override
	    public void fatalError(SAXParseException e) {
	        // do nothing
	    }

	    @Override
	    public void error(SAXParseException e) {
	        // do nothing
	    }
	    
	    @Override
	    public void warning(SAXParseException e) {
	        // do nothing
	    }
	}

	
	public void run() {
		System.out.println("Connected with client " + adr);
		
		String str = "";
		while(true) {
			try {
				str += in.readLine();
			} catch (SSLException ssl_e) {
				ssl_e.printStackTrace();
				return;
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			System.out.println(str);
			try {
				DocumentBuilder builder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
				builder.setErrorHandler(new NullErrorHandler());
				Document doc = builder.parse(new InputSource(new StringReader(str)));
				
				doc.getDocumentElement().normalize();

		        NodeList nList = doc.getElementsByTagName("sensorData");

		        for (int i = 0; i < nList.getLength(); i++) {

		            Node nNode = nList.item(i);

		            if (nNode.getNodeType() == Node.ELEMENT_NODE) {

		                Element elem = (Element) nNode;

		                String uid = elem.getAttribute("id");

		                Optional<Node> node1 = Optional.ofNullable(elem.getElementsByTagName("Temperature").item(0));
		                String temperature = "";
		                if(node1.isPresent())
		                	temperature = node1.get().getTextContent();

		                Optional<Node> node2 = Optional.ofNullable(elem.getElementsByTagName("Humidity").item(0));
		                String humidity = "";
		                if(node2.isPresent())
		                	humidity = node2.get().getTextContent();

		                Optional<Node> node3 = Optional.ofNullable(elem.getElementsByTagName("Flame").item(0));
		                String flame = "";
		                if(node3.isPresent())
		                	flame = node3.get().getTextContent();
		                
		                Optional<Node> node4 = Optional.ofNullable(elem.getElementsByTagName("Current").item(0));
		                String current = "";
		                if(node4.isPresent())
		                	current = node4.get().getTextContent();
		                
		                Optional<Node> node5 = Optional.ofNullable(elem.getElementsByTagName("LSM6DSOXTR").item(0));
		                LSM6DSOXTR lsm6dsoxtr = null;
		                if(node5.isPresent()) {
		                	String x = null, y = null, z = null;
		                	NodeList list = node5.get().getChildNodes();
		                	for (int j = 0; j < list.getLength(); j++) {
		                		  Node n = list.item(j);
		                		  String name = n.getNodeName();
		                		  if(name.equals("x"))
		                			  x = n.getTextContent();
		                		  else if (name.equals("y"))
		                			  y = n.getTextContent();
		                		  else if (name.equals("z"))
		                			  z = n.getTextContent();
		                	}
		                	lsm6dsoxtr = new LSM6DSOXTR(x, y, z);
		                }
		                
		                Optional<Node> node6 = Optional.ofNullable(elem.getElementsByTagName("Co2").item(0));
		                String co2 = "";
		                if(node6.isPresent())
		                	co2 = node6.get().getTextContent();
		                
		                Message msg = new Message(uid, temperature, humidity, flame, current, co2, lsm6dsoxtr);
		                System.out.println("Load " + msg.toString());
		                out.println("OK");
		                return;
		            } else
		            	System.err.println("Errore codifica xml");
		        }
			} catch (SAXException e) {
			} catch (IOException e) {
			} catch (ParserConfigurationException e) {
			}			
		}
	}
}
