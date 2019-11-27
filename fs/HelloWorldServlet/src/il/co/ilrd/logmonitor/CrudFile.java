package il.co.ilrd.logmonitor;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import il.co.ilrd.crud.*;

public class CrudFile implements CRUD<String, Integer>{
    private final BufferedWriter writer; 
    
	public CrudFile(String fileName) throws IOException {
		File file = new File(fileName);
		if(!file.exists()) {
			file.createNewFile();
		}
		writer = new BufferedWriter(new FileWriter(file, true));
	}
	
	@Override
	public void close() throws Exception {
		writer.close();
	}
	
	@Override
	public Integer create(String text) {
		try {
			writer.write(text);
			writer.flush();
		} catch (IOException e) {
			return -1;
		}
		
		return 0;
	}

	@Override
	public String read(Integer id) {
		throw new UnsupportedOperationException();
	}

	@Override
	public void update(Integer id, String newData) {
		throw new UnsupportedOperationException();
	}

	@Override
	public void delete(Integer id) {
		throw new UnsupportedOperationException();
	}
}