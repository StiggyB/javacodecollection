package a03_a;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import javax.swing.JFileChooser;

public class JTreeFilesearch {
    static List<File> files = new ArrayList<File>();
    static List<File> directories = new ArrayList<File>();
    static String path = null;
    static File root = null;

    private static void dirlist(File fname) throws IOException {
        
        File tmp = new File(fname.getCanonicalPath());
        File fobj = fname;
        try {
            for (String filename : fobj.list()) {
                File cfobj = new File(fobj.getCanonicalPath() + File.separator + filename);
                if (cfobj.canRead()) {
                    if (cfobj.isDirectory()) {
                        dirlist(cfobj);                  
                    }// if
                    if (cfobj.isFile()) {
                        files.add(new File(cfobj.getPath()));
                    }// if
                }//if
            }// for
        }catch (Exception e) {
            // TODO Auto-generated catch block
            // e.printStackTrace();
            e.getMessage();
        }        
        directories.add(tmp);
    }// dirlist
	
	static File selectRoot() {
		JFileChooser jfc = new JFileChooser();	
		jfc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY); 
		int rc = jfc.showOpenDialog(null);
		if (rc == JFileChooser.APPROVE_OPTION) {
			System.out.println(jfc.getSelectedFile().getName() + " open successful.");
		}//if
		return new File(jfc.getSelectedFile().getAbsolutePath());
	}//selectRoot
	
	public static void main(String[] args) {

		try {
			root = selectRoot();
			dirlist(new File(root.getAbsolutePath()));
			System.out.println("Einlesen fertig!\n");
		} catch (IOException e) {
			System.out.println(e.getMessage());
			e.printStackTrace();
		}//catch
	}//main
}
