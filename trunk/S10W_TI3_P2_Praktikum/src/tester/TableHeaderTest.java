package tester;

import java.awt.Component;
import java.awt.Color;
import javax.swing.*;
import javax.swing.table.JTableHeader;
//import javax.swing.table.DefaultTableColumnModel;
import javax.swing.table.TableColumnModel;
import javax.swing.table.TableColumn;
import javax.swing.table.TableCellRenderer;
 
 
 
class TableHeaderTest {
    
    public static void main(String[] args) {
        // JTable initialisieren und mit Inhalt füllen; siehe dazu Teil 2
        JTable table = new JTable(new String[][]{{"1", "2", "3"},{"4", "5", "6"}}, new String[]{"A", "B", "C"});
        
        // JTableHeader holen
        JTableHeader header = table.getTableHeader();
        
        // ColumnModel holen:
        TableColumnModel columnModel = header.getColumnModel();
        
        // TableColumn erstellen
        TableColumn aColumn = new TableColumn();
        // setHeaderValue() setzt den Titel
        aColumn.setHeaderValue("D");
        // modelIndex zeigt an von welcher Spalte im DatenModel die neue Spalte ihre Werte holen soll
        aColumn.setModelIndex(1); // Index 1 im Model sind also "2" und "5"
        columnModel.addColumn(aColumn);
        
        // eine spalte verschieben
        columnModel.moveColumn(0, 2); // spalte 0 (mit Tiel "A") verschieben an position 2 im model
        
        // spalten nicht resizable machen, nicht zulassen dass die spaltenreihenfolge geändert werden kann
        header.setResizingAllowed(false);
        header.setReorderingAllowed(false);
        
        // Renderer zuweisen
        header.setDefaultRenderer(new MyHeaderCellRenderer());
        
        // JFrame konstruieren
        JFrame frame = new JFrame("JTableHeader test");
        // Table in JScrollPane einfügen und dem Frame hinzufügen
        frame.getContentPane().add(new JScrollPane(table));
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
    }
}
 
 
// Eigener CellRenderer für die spaltenköpfe. Liefert immer ein 
// JLabel zurück, und implementiert TableCellRenderer
class MyHeaderCellRenderer extends JLabel implements TableCellRenderer {
    
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	// einzig wichtige methode
    public Component getTableCellRendererComponent(JTable table, Object value, 
            boolean isSelected, boolean hasFocus, int row, int column) {
        // text
        setText(value.toString());
        // normale schriftart
        setFont(table.getFont());
        // der standard rahmen für spaltenköpfe
        setBorder(UIManager.getBorder("TableHeader.cellBorder"));
        // text zentiriert darstellen
        setHorizontalAlignment(SwingConstants.CENTER);
        // tooltip
        setToolTipText("Colum No. "+(column+1));
        // undurchsichtig damit man die hintergrundfarbe sieht.
        setOpaque(true);
        // je nach spalte die hintergrundfarbe setzen
        switch(column) {
            case 0:  setBackground(Color.GREEN); break;
            case 1:  setBackground(Color.BLUE); break;
            case 2:  setBackground(Color.YELLOW); break;
            case 3:  setBackground(Color.RED); break;
            default: setBackground(Color.LIGHT_GRAY);
        }
        return this;
    }
}
