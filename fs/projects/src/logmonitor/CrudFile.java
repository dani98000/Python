package logmonitor;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import il.co.ilrd.crud.*;

public class CrudFile implements Crud<String, Integer>{
	private String fileName;
	private File file;
	private RandomAccessFile raf;
	
	public CrudFile(String fileName) {
		this.fileName = fileName;
		file = new File(fileName);
		if(!file.exists()) {
			try {
				file.createNewFile();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		try {
			raf = new RandomAccessFile(file,"rw");
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}

	public String getFileName() {
		return fileName;
	}
	
	@Override
	public void close() throws Exception {
		raf.close();
	}

	@Override
	public Integer Create(String text) {
		try {
			raf.seek(file.length());
			raf.writeChars(text);
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return null;
	}

	@Override
	public String Read(Integer id) {
		throw new UnsupportedOperationException();
	}

	@Override
	public void Update(Integer id, String newData) {
		throw new UnsupportedOperationException();
	}

	@Override
	public void Delete(Integer id) {
		throw new UnsupportedOperationException();
	}
}