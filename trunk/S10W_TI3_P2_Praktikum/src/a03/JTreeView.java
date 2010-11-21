package a03;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.JTree;
import javax.swing.event.TreeExpansionEvent;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.event.TreeWillExpandListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.ExpandVetoException;
import javax.swing.tree.TreeModel;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;
import javax.swing.tree.TreeSelectionModel;

/**
 * Praktikum: P2P<br>
 * Semester: WS10<br>
 * Aufgaben-Nr.: 03<br>
 * 
 * Version: V0<br>
 * Aenderungen:
 * 
 * Quellen: API, Swing, JavaTutorials, Buch: Java als erste Programmiersprache
 * 
 * @author Mueller-Pettenpohl, Tell #1989982, Rumpf, Soeren #1971654<br>
 */

public class JTreeView extends JPanel {

    private static final long serialVersionUID = 1L;
    private File root;
    private DefaultMutableTreeNode nRoot;
    private List<File> directories = new ArrayList<File>();
    private List<File> files = new ArrayList<File>();
    private JScrollPane treeScroller;
    private JScrollPane infoScroller;
    private JPanel mainArea = new JPanel();
    private JTextField info = new JTextField();
    private JTree tree;

    public JTreeView() throws IOException {
        createJTree();
        createTreeArea();
        createInfoArea();
        createMainArea();
    }// JTreeView()

    public List<File> getDirectories() {
        return directories;
    }// getDirectories

    public List<File> getFiles() {
        return files;
    }// getFiles

    private File selectRoot() {
        JFileChooser jfc = new JFileChooser();
        jfc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        int rc = jfc.showOpenDialog(null);
        if (rc == JFileChooser.APPROVE_OPTION) {
            System.out.println(jfc.getSelectedFile().getName() + " open successful.");
            return new File(jfc.getSelectedFile().getAbsolutePath());
        }else{
            return null;
        }//else
    }// selectRoot

    private void createJTree() throws IOException {
        // Select Root
        root = selectRoot();
        if (root != null) {
            nRoot = new DefaultMutableTreeNode(new FileInfo(root, "root"));
            for (File a : root.listFiles()) {
                File thisFile = a;
                if (thisFile.canRead()) {
                    if (thisFile.isDirectory()) {
                        directories.add(thisFile);
                        nRoot.add(showFiles(a));
                    }else {
                        files.add(thisFile);
                        nRoot.add(new DefaultMutableTreeNode(new FileInfo(thisFile)));
                    }// else
                }// if
            }// for
        }else{
            nRoot = null;
            JOptionPane.showMessageDialog(null,"Error: Aborted directory selection. Exiting program.",
                    "Directory selection error", JOptionPane.WARNING_MESSAGE);
            System.exit(0);
        }//else
    }// createJTree

    private DefaultMutableTreeNode showFiles(File f) throws IOException {
        File actualFile = f;
        DefaultMutableTreeNode node = new DefaultMutableTreeNode(new FileInfo(actualFile));
        try {
            for (String filename : actualFile.list()) {
                File cfobj = new File(actualFile.getCanonicalPath() + File.separator + filename);
                if (cfobj.canRead()) {
                    if (cfobj.isDirectory()) {
                        node.add(showFiles(cfobj));
                    }else {
                        node.add(new DefaultMutableTreeNode(new FileInfo(cfobj)));
                    }// if
                }// if
            }// for
        }catch (Exception e) {
            e.printStackTrace();
        }// catch
        return node;
    }// showFiles

    private void createMainArea() {
        mainArea.setLayout(new BorderLayout());
        mainArea.setPreferredSize(new Dimension(600, 450));
        mainArea.add(BorderLayout.CENTER, treeScroller);
        mainArea.add(BorderLayout.SOUTH, infoScroller);
        ShowInFrame.show("JTree", mainArea);
    }// createMainArea

    private void createInfoArea() {
        infoScroller = new JScrollPane(info);
        infoScroller.setPreferredSize(new Dimension(600, 50));
        infoScroller.setVisible(true);
    }// createInfoArea

    private void createTreeArea() {
        // Datenmodell erstellen
        TreeModel treeModel = new DefaultTreeModel(nRoot);
        // Baum erzeugen
        tree = new JTree(treeModel);
        tree.getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);
        tree.setVisible(true);
        // TreeListener registrieren
        tree.addTreeWillExpandListener(new TreeListener());
        tree.addTreeSelectionListener(new TreeListener());
        treeScroller = new JScrollPane(tree);
        treeScroller.setVisible(true);
    }// createTreeArea

    class TreeListener implements TreeWillExpandListener, TreeSelectionListener {
        // zuletzt ge�ffneter Pfad
        private TreePath path;

        // wird aufgerufen, bevor der Knoten geoeffnet wird
        public void treeWillExpand(TreeExpansionEvent e) throws ExpandVetoException {
            JTree baum = (JTree) e.getSource(); // Eventquelle ermitteln
            path = e.getPath(); // aktuell ausgewaehlten Pfad ermitteln
            TreeNode wurzel = // Wurzelknoten ermitteln
            (TreeNode) baum.getModel().getRoot();
            TreePath wurzelPfad = // Cast von Knoten zu Pfad
            new TreePath(wurzel);

            if (!e.getPath().equals(wurzelPfad))// Wurzel ignorieren
            {
                if (path != null) // Wenn ein Pfad ge�ffnet
                    baum.collapsePath(path); // ist, dann schlie�en
                path = e.getPath(); // ge�ffneten Pfad sichern
            }// if
        }// treeWillExpand

        // wird aufgerufen, bevor der Knoten geschlossen wird
        public void treeWillCollapse(TreeExpansionEvent e) throws ExpandVetoException {

        }// treeWillCollapse

        @Override
        public void valueChanged(TreeSelectionEvent e) {
            // Returns the last path element of the selection.
            // Liefert das letzte Pfad Element der Auswahl
            DefaultMutableTreeNode node = (DefaultMutableTreeNode) tree.getLastSelectedPathComponent();
            if (node == null)
                //
                return;
            Object nodeInfo = node.getUserObject();
            if (node.isLeaf()) {
                FileInfo selectedFile = (FileInfo) nodeInfo;
                info.setText(String.format("%s%s%s%s   %40s %19d B %30s", selectedFile.getFile().isDirectory() ? "d"
                        : "-", selectedFile.getFile().canRead() ? "r" : "-", selectedFile.getFile().canWrite() ? "w"
                        : "-", selectedFile.getFile().canExecute() ? "x" : "-", selectedFile.getFile()
                        .getAbsoluteFile(), selectedFile.getFile().length(), new Date(selectedFile.getFile()
                        .lastModified()).toString()));
            }else {
                // info.setText(null);
                FileInfo selectedDir = (FileInfo) nodeInfo;
                info.setText(String.format("%s%s%s%s   %40s %19d B %30s", selectedDir.getFile().isDirectory() ? "d"
                        : "-", selectedDir.getFile().canRead() ? "r" : "-", selectedDir.getFile().canWrite() ? "w"
                        : "-", selectedDir.getFile().canExecute() ? "x" : "-", selectedDir.getFile().getAbsoluteFile(),
                        selectedDir.getFile().length(), new Date(selectedDir.getFile().lastModified()).toString()));
            }// else
        }// valueChanged
    }// baumListener

    public static void main(String[] args) throws IOException {
        JTreeView fenster = new JTreeView();
        fenster.setVisible(true);
    }// main

}// JTreeView
