package chatroomV2;

import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.util.function.BiConsumer;
import java.util.function.Consumer;

import javax.swing.*;

public class ClientGUI extends JFrame{
	private final int WIDTH = 1000;
	private final int HEIGHT = 600;
	private String TITLE = "The Best Chat Server In The Entire Room";  
	private String ip;
	private int portNum;

    private final JSplitPane splitPane; 
    private final JPanel topPanel;       
    private final JPanel bottomPanel;   
    private final JScrollPane scrollPane; 
    private JTextArea textArea;     
    private final JPanel inputPanel;     
    private final JTextField textField;  
    private final JButton button;   
    
    private BiConsumer<String, Integer> onConnect;
    Consumer<String> onMessage;
	
	public ClientGUI() {
		splitPane = new JSplitPane();

        topPanel = new JPanel();    
        initTopPanel(topPanel);
        bottomPanel = new JPanel(); 

        scrollPane = new JScrollPane(); 
        textArea = new JTextArea();      
        PrintStream printStream = new PrintStream(new CustomOutputStream(textArea));
        System.setOut(printStream);
        System.setErr(printStream);

        inputPanel = new JPanel();
        textField = new JTextField();  
        button = new JButton("send"); 
        button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
            	if(button.isEnabled()) {
            		onMessage.accept(textField.getText());
            		textField.setText("");
            	}	
            }
        });

        setPreferredSize(new Dimension(400, 400));    
        getContentPane().setLayout(new GridLayout()); 
        getContentPane().add(splitPane);              

        splitPane.setOrientation(JSplitPane.VERTICAL_SPLIT);  
        splitPane.setDividerLocation(200);                    
        splitPane.setTopComponent(topPanel);                  
        splitPane.setBottomComponent(bottomPanel);            

        bottomPanel.setLayout(new BoxLayout(bottomPanel, BoxLayout.Y_AXIS));

        bottomPanel.add(scrollPane);       
        scrollPane.setViewportView(textArea);    
        bottomPanel.add(inputPanel);                

        inputPanel.setMaximumSize(new Dimension(Integer.MAX_VALUE, 75));    
        inputPanel.setLayout(new BoxLayout(inputPanel, BoxLayout.X_AXIS));  

        inputPanel.add(textField);        
        inputPanel.add(button);        
        inputPanel.getRootPane().setDefaultButton(button);

        pack();   
    }

    private void initTopPanel(JPanel topPanel) {
    	final JTextField IP;
    	final JTextField port;
        final JButton connectButton; 
        
        IP = new HintTextField("Please enter IP");
        IP.setEditable(true);
        System.out.println(IP.getText());
        port = new HintTextField("Please enter Port");
        port.setEditable(true);
        System.out.println(port.getText());
        connectButton = new JButton("connect!!!");
        connectButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
            	if(connectButton.isEnabled()) {
	            	onConnect.accept(IP.getText(),Integer.parseInt(port.getText()));
            	}
            }
        });
        topPanel.add(IP);
        topPanel.add(port);
        topPanel.add(connectButton);
	}
    
    class HintTextField extends JTextField implements FocusListener {

    	  private final String hint;
    	  private boolean showingHint;

    	  public HintTextField(final String hint) {
    	    super(hint);
    	    this.hint = hint;
    	    this.showingHint = true;
    	    super.addFocusListener(this);
    	  }

    	  @Override
    	  public void focusGained(FocusEvent e) {
    	    if(this.getText().isEmpty()) {
    	      super.setText("");
    	      showingHint = false;
    	    }
    	  }
    	  @Override
    	  public void focusLost(FocusEvent e) {
    	    if(this.getText().isEmpty()) {
    	      super.setText(hint);
    	      showingHint = true;
    	    }
    	  }

    	  @Override
    	  public String getText() {
    	    return showingHint ? "" : super.getText();
    	  }
    	}

	public void registerOnConnect(BiConsumer<String, Integer> onConnect) {
		this.onConnect = onConnect;
	}
	
	public void registerOnMessage(Consumer<String> onMessage) {
		this.onMessage = onMessage;
	}
	
	public class CustomOutputStream extends OutputStream {
	    private JTextArea textArea;

	    public CustomOutputStream(JTextArea textArea) {
	        this.textArea = textArea;
	    }

	    @Override
	    public void write(int b) throws IOException {
	        // redirects data to the text area
	        textArea.append(String.valueOf((char)b));
	        // scrolls the text area to the end of data
	        textArea.setCaretPosition(textArea.getDocument().getLength());
	        // keeps the textArea up to date
	        textArea.update(textArea.getGraphics());
	    }
	}
}
