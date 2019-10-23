package crud;

import java.io.File;
import java.util.function.Predicate;

public class FileCrud implements Crud<File,String>{

	@Override
	public void Create(File entry) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public File Read(int id) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public boolean Update(int id, Predicate<File> updateFunction) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void Delete(int id) {
		// TODO Auto-generated method stub
		
	}
	
}
