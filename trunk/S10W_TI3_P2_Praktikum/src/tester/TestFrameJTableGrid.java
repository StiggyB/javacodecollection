package tester;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
 
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTable;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.TableCellRenderer;
 
public class TestFrameJTableGrid
    extends JFrame
{
 
  /**
	 * 
	 */
	private static final long serialVersionUID = 1L;

public TestFrameJTableGrid()
  {
    setDefaultCloseOperation(EXIT_ON_CLOSE);
 
    JTable table = new JTable(new AliveTableModel());
 
    table.setDefaultRenderer(Object.class, new AliveCellRenderer());
 
    table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
 
    table.setRowHeight(50);
    
    table.setValueAt(true, 5, 5);
    table.setValueAt(true, 1, 2);
    
    JPanel panel = new JPanel();
    panel.add(table);
    add(panel, BorderLayout.CENTER);
   
    pack();
  }
 
  private class AliveTableModel
      extends AbstractTableModel
  {
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private Boolean[][] alive = new Boolean[10][10];
    
    public AliveTableModel()
    {
      for (int i = 0; i < alive.length; i++)
      {
        for (int j = 0; j < alive[i].length; j++)
        {
          alive[i][j] = new Boolean(false);
        }
      }
    }
 
    public int getColumnCount()
    {
      return alive[0].length;
    }
 
    public int getRowCount()
    {
      return alive.length;
    }
 
    public Object getValueAt(int rowIndex, int columnIndex)
    {
      return alive[rowIndex][columnIndex];
    }
    
    @Override
    public void setValueAt(Object aValue, int rowIndex, int columnIndex)
    {
      alive[rowIndex][columnIndex] = (Boolean)aValue;
    }
 
  }
 
  private class AliveCellRenderer
      extends JLabel
      implements TableCellRenderer
  {
 
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private Color blue   = new Color(62, 101, 241);
    private Color yellow = new Color(247, 250, 137);
 
    public AliveCellRenderer()
    {
      setOpaque(true);
    }
 
    public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column)
    {
      Boolean alive = (Boolean) value;
 
      if (alive.booleanValue())
      {
        setBackground(blue);
      }
      else
      {
        setBackground(yellow);
      }
      return this;
    }
 
  }
 
  public static void main(String[] args)
  {
    new TestFrameJTableGrid().setVisible(true);
  }
}
