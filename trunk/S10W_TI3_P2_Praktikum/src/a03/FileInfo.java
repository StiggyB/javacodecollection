package a03_a;

import java.io.File;

public class FileInfo {
    private File file;
    private String info;

    public File getFile() {
        return file;
    }// getFile

    FileInfo(File f) {
        this.file = f;
    }// FileInfo

    FileInfo(File f, String s) {
        this.file = f;
        this.info = s;
    }

    public String toString() {
        if(this.info == "root"){
            return this.file.getPath();
        }else
        return this.file.getName();
    }// toString
}
