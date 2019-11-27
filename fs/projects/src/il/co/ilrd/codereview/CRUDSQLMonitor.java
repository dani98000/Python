package il.co.ilrd.codereview;

import il.co.ilrd.logmonitor.LogMonitor;

public class CRUDSQLMonitor {
	
	public static void main(String[] args) throws Exception {
		   LogMonitor monitor = new LogMonitor("/var/log/syslog");
	        CRUDSQL crud = new CRUDSQL("jdbc:mysql://localhost:3306/LogBackup?useSLL=false", "sandra", "sandra");
	        monitor.registerEventHandler(crud::create);
	        monitor.start(); 
	        Thread.sleep(100000);
	        monitor.stop();
	        crud.close();

		
		
		
		/*@SuppressWarnings("resource")
		CRUDSQL crud = new CRUDSQL("jdbc:mysql://localhost:3306/LogBackup?useSLL=false", "sandra", "sandra");
		//                           DRIVER /LOCAL HOST / DEFULT PORT/DATABASE NAME
		Server server = new UDPServer();
		
		
		server.registerOnNewMessage((String s)-> {
			System.out.println("Server " + s);
			crud.create(s);
		});
		try {
			server.start();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	*/	
	}
}
