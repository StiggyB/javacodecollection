package tester;

public class Trial extends javax.swing.JFrame{
	
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private javax.swing.JLabel a;
	
    public Trial() {
        a = new javax.swing.JLabel();
        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        a.setIcon(new javax.swing.ImageIcon("images/images1.jpg"));
        add(a);
        pack();
    }
    
    public static void main(String args[]){
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new Trial().setVisible(true);
            }
        });
    }

}
