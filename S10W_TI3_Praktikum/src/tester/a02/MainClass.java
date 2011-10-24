package tester.a02;

import java.awt.BorderLayout;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTable;

public class MainClass {
  public static void main(String args[]) {
    String rows[][] = { { "A", "a" }, { "B", "b" }, { "E", "e" } };
    String headers[] = { "Upper", "Lower" };

    final int modeKey[] = { JTable.AUTO_RESIZE_ALL_COLUMNS, JTable.AUTO_RESIZE_LAST_COLUMN,
        JTable.AUTO_RESIZE_NEXT_COLUMN, JTable.AUTO_RESIZE_OFF,
        JTable.AUTO_RESIZE_SUBSEQUENT_COLUMNS };

    final JTable table = new JTable(rows, headers);
    JScrollPane scrollPane = new JScrollPane(table);

    String modes[] = { "Resize All Columns", "Resize Last Column", "Resize Next Column",
        "Resize Off", "Resize Subsequent Columns" };
    
    
    final JComboBox resizeModeComboBox = new JComboBox(modes);
    int defaultMode = 4;
    table.setAutoResizeMode(modeKey[defaultMode]);
    resizeModeComboBox.setSelectedIndex(defaultMode);
    ItemListener itemListener = new ItemListener() {
      public void itemStateChanged(ItemEvent e) {
        int index = resizeModeComboBox.getSelectedIndex();
        table.setAutoResizeMode(modeKey[index]);
      }
    };
    resizeModeComboBox.addItemListener(itemListener);

    JFrame frame = new JFrame("Resizing Table");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    frame.add(resizeModeComboBox, BorderLayout.NORTH);
    frame.add(scrollPane, BorderLayout.CENTER);

    frame.setSize(300, 150);
    frame.setVisible(true);
  }
}
