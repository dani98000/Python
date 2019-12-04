package il.co.ilrd.mysql;

import il.co.ilrd.logmonitor.LogMonitor;

public class TestCrudSQL {
	public static void main(String[] args) throws InterruptedException {
		try(CrudSQLLogMonitor crud = new CrudSQLLogMonitor("test", "log2", "daniel","ct,h kvmkhj")) {
		LogMonitor monitor = new LogMonitor("/var/log/syslog");
		monitor.registerEventHandler((String msg) -> {
			int id = crud.create(msg);
			//System.out.println(crud.read(id));
		});	
		monitor.start();
		Thread.sleep(1000000);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
