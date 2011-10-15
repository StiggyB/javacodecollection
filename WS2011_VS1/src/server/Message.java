package server;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;

public class Message {
	
    private int id;
    private String clientId;
    private DateFormat dateFormat;
    private Calendar cal;
    private String timestamp;
    private String msg;
    
    public Message(int id, String clientId, String msg) {
        this.id = id;
        this.clientId = clientId;
        this.msg = msg;
        this.dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
        this.cal = Calendar.getInstance();
        this.timestamp = dateFormat.format(cal.getTime());
    }
    
    public String getTimestamp() {
		return timestamp;
	}

	public int getId() {
        return id;
    }
    
    public String getClientId() {
        return clientId;
    }
    
    public String getMsg() {
        return msg;
    }
    
    @Override
    public boolean equals(Object o) {
		return ((Message)o).id == (this.id) ? true : false;
    }

	@Override
	public String toString() {
		return "<" + id + ">" + "<" + clientId + ">" + ": " + "<" + msg + ">" + "<" + timestamp + ">";
	}
    
}
