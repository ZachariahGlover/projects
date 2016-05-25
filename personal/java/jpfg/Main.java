package jpfg;

import java.awt.geom.AffineTransform;
import java.awt.image.AffineTransformOp;
import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.util.Random;
import javax.imageio.ImageIO;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

public class Main extends javax.swing.JFrame {
    
    Random rand;
    byte[] byteImage, newByteImage;
    byte[] byteImageHolder;
    String folderPath, imagePath;
    
    int min, max;
    
    public Main() {
        initComponents();
        
        java.awt.Dimension dim = java.awt.Toolkit.getDefaultToolkit().getScreenSize();
        this.setLocation(dim.width/2-this.getSize().width/2, dim.height/2-this.getSize().height/2);
        
        rand = new Random(System.currentTimeMillis());
    }

    private void initComponents() {

        mutateButton = new javax.swing.JButton();
        selectImageButton = new javax.swing.JButton();
        imageNameField = new javax.swing.JTextField();
        saveLabel = new javax.swing.JLabel();
        owIntensitySlider = new javax.swing.JSlider();
        sIterationsSlider = new javax.swing.JSlider();
        aIterationsSlider = new javax.swing.JSlider();
        dIterationsSlider = new javax.swing.JSlider();
        owLabel = new javax.swing.JLabel();
        sLabel = new javax.swing.JLabel();
        aLabel = new javax.swing.JLabel();
        dLabel = new javax.swing.JLabel();
        mLabel = new javax.swing.JLabel();
        mIterationsSlider = new javax.swing.JSlider();
        screenSep = new javax.swing.JSeparator();
        saveButton = new javax.swing.JButton();
        owRand = new javax.swing.JRadioButton();
        owZero = new javax.swing.JRadioButton();
        imagePanel = new javax.swing.JPanel();
        aRand = new javax.swing.JRadioButton();
        aZero = new javax.swing.JRadioButton();
        resetParamsButton = new javax.swing.JButton();
        owIterationsSlider = new javax.swing.JSlider();
        owIterLabel = new javax.swing.JLabel();
        owIntLabel = new javax.swing.JLabel();
        paramSep0 = new javax.swing.JSeparator();
        aIterLabel = new javax.swing.JLabel();
        aIntLabel = new javax.swing.JLabel();
        mIntensitySlider = new javax.swing.JSlider();
        paramSep1 = new javax.swing.JSeparator();
        dIntLabel = new javax.swing.JLabel();
        dIterLabel = new javax.swing.JLabel();
        aIntensitySlider = new javax.swing.JSlider();
        paramSep2 = new javax.swing.JSeparator();
        sIterLabel = new javax.swing.JLabel();
        sIntLabel = new javax.swing.JLabel();
        dIntensitySlider = new javax.swing.JSlider();
        paramSep3 = new javax.swing.JSeparator();
        mIterLabel = new javax.swing.JLabel();
        mIntLabel = new javax.swing.JLabel();
        sIntensitySlider = new javax.swing.JSlider();
        paramSep4 = new javax.swing.JSeparator();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setFocusable(false);
        setResizable(false);

        mutateButton.setEnabled(false);
        mutateButton.setFocusable(false);
        mutateButton.setLabel("mutate It");
        mutateButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                mutateButtonPress(evt);
            }
        });

        selectImageButton.setText("Select Image");
        selectImageButton.setToolTipText("");
        selectImageButton.setFocusable(false);
        selectImageButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                selectImagePress(evt);
            }
        });

        imageNameField.setText("mutate");

        saveLabel.setText("Save Image As:");
        saveLabel.setFocusable(false);

        owIntensitySlider.setMaximum(24);
        owIntensitySlider.setMinimum(8);
        owIntensitySlider.setSnapToTicks(true);
        owIntensitySlider.setValue(0);
        owIntensitySlider.setFocusable(false);

        sIterationsSlider.setMaximum(64);
        sIterationsSlider.setSnapToTicks(true);
        sIterationsSlider.setValue(0);
        sIterationsSlider.setFocusable(false);

        aIterationsSlider.setMaximum(64);
        aIterationsSlider.setSnapToTicks(true);
        aIterationsSlider.setValue(0);
        aIterationsSlider.setFocusable(false);

        dIterationsSlider.setMaximum(32);
        dIterationsSlider.setSnapToTicks(true);
        dIterationsSlider.setValue(0);
        dIterationsSlider.setFocusable(false);

        owLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        owLabel.setText("Overwrite");

        sLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        sLabel.setText("Swap");
        sLabel.setFocusable(false);

        aLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        aLabel.setText("Add");
        aLabel.setFocusable(false);

        dLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        dLabel.setText("Delete");
        dLabel.setFocusable(false);

        mLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        mLabel.setText("Move");
        mLabel.setFocusable(false);

        mIterationsSlider.setMaximum(64);
        mIterationsSlider.setSnapToTicks(true);
        mIterationsSlider.setValue(0);
        mIterationsSlider.setFocusable(false);

        screenSep.setOrientation(javax.swing.SwingConstants.VERTICAL);

        saveButton.setText("Save It");
        saveButton.setEnabled(false);
        saveButton.setFocusable(false);
        saveButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                savePress(evt);
            }
        });

        owRand.setText("Random");
        owRand.setFocusable(false);
        owRand.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                owrSelect(evt);
            }
        });

        owZero.setSelected(true);
        owZero.setText("Zeroes");
        owZero.setFocusable(false);
        owZero.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                owzSelect(evt);
            }
        });

        imagePanel.setFocusable(false);

        javax.swing.GroupLayout imagePanelLayout = new javax.swing.GroupLayout(imagePanel);
        imagePanel.setLayout(imagePanelLayout);
        imagePanelLayout.setHorizontalGroup(
            imagePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 594, Short.MAX_VALUE)
        );
        imagePanelLayout.setVerticalGroup(
            imagePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 0, Short.MAX_VALUE)
        );

        aRand.setText("Random");
        aRand.setFocusable(false);
        aRand.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                arSelect(evt);
            }
        });

        aZero.setSelected(true);
        aZero.setText("Zeroes");
        aZero.setFocusable(false);
        aZero.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                azSelect(evt);
            }
        });

        resetParamsButton.setText("Reset");
        resetParamsButton.setFocusable(false);
        resetParamsButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                resetButton(evt);
            }
        });

        owIterationsSlider.setMaximum(64);
        owIterationsSlider.setSnapToTicks(true);
        owIterationsSlider.setValue(0);
        owIterationsSlider.setFocusable(false);

        owIterLabel.setText("Iterations");
        owIterLabel.setFocusable(false);

        owIntLabel.setText("Intensity");
        owIntLabel.setFocusable(false);

        aIterLabel.setText("Iterations");
        aIterLabel.setFocusable(false);

        aIntLabel.setText("Intensity");
        aIntLabel.setFocusable(false);

        mIntensitySlider.setMaximum(24);
        mIntensitySlider.setMinimum(8);
        mIntensitySlider.setSnapToTicks(true);
        mIntensitySlider.setValue(0);
        mIntensitySlider.setFocusable(false);

        dIntLabel.setText("Intensity");
        dIntLabel.setFocusable(false);

        dIterLabel.setText("Iterations");
        dIterLabel.setFocusable(false);

        aIntensitySlider.setMaximum(24);
        aIntensitySlider.setMinimum(8);
        aIntensitySlider.setSnapToTicks(true);
        aIntensitySlider.setValue(0);
        aIntensitySlider.setFocusable(false);

        sIterLabel.setText("Iterations");
        sIterLabel.setFocusable(false);

        sIntLabel.setText("Intensity");
        sIntLabel.setFocusable(false);

        dIntensitySlider.setMaximum(24);
        dIntensitySlider.setMinimum(8);
        dIntensitySlider.setSnapToTicks(true);
        dIntensitySlider.setValue(0);
        dIntensitySlider.setFocusable(false);

        mIterLabel.setText("Iterations");
        mIterLabel.setFocusable(false);

        mIntLabel.setText("Intensity");
        mIntLabel.setFocusable(false);

        sIntensitySlider.setMaximum(24);
        sIntensitySlider.setMinimum(8);
        sIntensitySlider.setSnapToTicks(true);
        sIntensitySlider.setValue(0);
        sIntensitySlider.setFocusable(false);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(saveLabel)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(imageNameField))
                    .addComponent(mutateButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(saveButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(selectImageButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(paramSep0, javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(aLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(owIterLabel)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(owIterationsSlider, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE))
                    .addComponent(paramSep1)
                    .addComponent(dLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(paramSep2)
                    .addComponent(sLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(paramSep3, javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(mLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(paramSep4)
                    .addComponent(resetParamsButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(owIntLabel)
                        .addGap(8, 8, 8)
                        .addComponent(owIntensitySlider, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE))
                    .addComponent(owLabel, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(aIterLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(aIntLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 47, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(aIntensitySlider, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE)
                            .addComponent(aIterationsSlider, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE)))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(dIterLabel)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(dIterationsSlider, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(dIntLabel)
                        .addGap(8, 8, 8)
                        .addComponent(dIntensitySlider, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(sIterLabel)
                            .addComponent(sIntLabel))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(sIntensitySlider, javax.swing.GroupLayout.DEFAULT_SIZE, 161, Short.MAX_VALUE)
                            .addComponent(sIterationsSlider, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE)))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(mIterLabel)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(mIterationsSlider, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(owRand)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(owZero))
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(aRand)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(aZero)))
                        .addGap(0, 0, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(mIntLabel)
                        .addGap(8, 8, 8)
                        .addComponent(mIntensitySlider, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(screenSep, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(imagePanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(imagePanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(screenSep, javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                        .addComponent(owLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 15, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(owIterLabel, javax.swing.GroupLayout.DEFAULT_SIZE, 19, Short.MAX_VALUE)
                            .addComponent(owIterationsSlider, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(owIntensitySlider, javax.swing.GroupLayout.PREFERRED_SIZE, 18, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(owIntLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(owRand)
                            .addComponent(owZero))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(paramSep0, javax.swing.GroupLayout.PREFERRED_SIZE, 8, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(aLabel)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(aIterationsSlider, javax.swing.GroupLayout.PREFERRED_SIZE, 18, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(aIterLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 18, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(aIntensitySlider, javax.swing.GroupLayout.PREFERRED_SIZE, 18, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(aIntLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 18, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(aRand)
                            .addComponent(aZero))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(paramSep1, javax.swing.GroupLayout.PREFERRED_SIZE, 8, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(dLabel)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(dIterLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 18, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(dIterationsSlider, javax.swing.GroupLayout.PREFERRED_SIZE, 18, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(dIntLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 18, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(dIntensitySlider, javax.swing.GroupLayout.PREFERRED_SIZE, 18, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(paramSep2, javax.swing.GroupLayout.PREFERRED_SIZE, 8, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(sLabel)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(sIterationsSlider, javax.swing.GroupLayout.PREFERRED_SIZE, 18, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(sIterLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 18, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(sIntensitySlider, javax.swing.GroupLayout.PREFERRED_SIZE, 18, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(sIntLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(paramSep3, javax.swing.GroupLayout.PREFERRED_SIZE, 8, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(mLabel)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(mIterLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 18, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(mIterationsSlider, javax.swing.GroupLayout.PREFERRED_SIZE, 18, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(mIntLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 18, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(mIntensitySlider, javax.swing.GroupLayout.PREFERRED_SIZE, 18, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(paramSep4, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(resetParamsButton)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(selectImageButton)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(mutateButton)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(imageNameField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(saveLabel))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(saveButton)
                        .addGap(0, 0, Short.MAX_VALUE)))
                .addGap(6, 6, 6))
        );

        pack();
    }

    public void selectAndLoadImage() {
        JFileChooser fc;
        fc = new JFileChooser();
        int returnVal = fc.showOpenDialog(fc);
        if (returnVal == JFileChooser.APPROVE_OPTION) {
            File file = fc.getSelectedFile();
            try {
                imagePath = file.toPath().toString();
                
                if ((imagePath.toLowerCase().endsWith(".jpg")) || (imagePath.toLowerCase().endsWith(".jpeg"))) {
                    folderPath = imagePath.substring(0, imagePath.lastIndexOf("\\"));
                    byteImage = Files.readAllBytes(file.toPath());
                    createPreview(byteImage);
                    mutateButton.setEnabled(true);
                } else {
                    JOptionPane.showMessageDialog(null, "jpgs only kthnx", "Error", JOptionPane.ERROR_MESSAGE);
                }
            } catch (IOException ex) {
                System.out.println(ex.getMessage());
            }
        }
    }
    
    public void createPreview(byte [] bI) {
        try {
            InputStream isI = new ByteArrayInputStream(bI);
            BufferedImage buffI = ImageIO.read(isI);
            
            int w = buffI.getWidth();
            int h = buffI.getHeight();
            
            if ((w > imagePanel.getWidth()) || (h > imagePanel.getHeight())) {
                
                int diffW = w - imagePanel.getWidth();
                int diffH = h - imagePanel.getHeight();
                double scale = 1.0;

                if (diffW > diffH) {
                    scale = ((double) imagePanel.getWidth()) / ((double) w);
                } else {
                    scale = ((double) imagePanel.getHeight()) / ((double) h);
                }
                
                BufferedImage scaledI = new BufferedImage(w, h, BufferedImage.TYPE_INT_ARGB);
                AffineTransform at = new AffineTransform();
                at.scale(scale, scale);
                AffineTransformOp scaleOp = new AffineTransformOp(at, AffineTransformOp.TYPE_BILINEAR);
                scaledI = scaleOp.filter(buffI, scaledI);

                
                int rw = (int) (((double) w) * scale);
                int rh = (int) (((double) h) * scale);
                int px = (imagePanel.getWidth() - rw) / 2;
                int py = (imagePanel.getHeight() - rh) / 2;
                
                imagePanel.getGraphics().clearRect(0, 0, imagePanel.getWidth(), imagePanel.getHeight());
                imagePanel.getGraphics().drawImage(scaledI, px + 1, py + 1, this);
                
            } else {
                imagePanel.getGraphics().drawImage(buffI, 0, 0, this);
            }
        } catch (IOException ex) {
            ex.getMessage();
        }
    }
    
    // ---
    
    public void overwriteBytes(int segLen, int numO, byte[] work, boolean r) {
        
        byte [] randBytes;
        
        int b0;
        
        for (int i = 0; i < numO; i++) {
            b0 = rand.nextInt(max - min - (segLen + 1)) + min;

            randBytes = new byte[segLen];
            
            if (r) {
                rand.nextBytes(randBytes);
            } else {
                for (byte rb : randBytes) {
                    rb = (byte) 0;
                }
            }
            
            for (int j = 0; j < segLen; j++) {
                work[b0 + j] = randBytes[j];
            }
        }
    }

    public void swapBytes(int segLen, int numS, byte [] work, byte [] backup) {
        
        int b0, b1;
        
        for (int i = 0; i < numS; i++) {
            b0 = rand.nextInt(max - min - (segLen + 1)) + min;
            b1 = rand.nextInt(max - min - (segLen + 1)) + min;

            while (b1 >= b0 && b1 <= (b0 + segLen)) {
                b1 = rand.nextInt(max - min - (segLen + 1)) + min;
            }

            for (int j = 0; j < segLen; j++) {
                work[b0 + j] = backup[b1 + j];
                work[b1 + j] = backup[b0 + j];
            }
        }
    }
    
    public void moveBytes(int segLen, int numM, byte [] work) {
        
        byte [] byteHolder;
        int b0, b1;
        
        for (int i = 0; i < numM; i++) {

            byteHolder = new byte[work.length];
            for (int j = 0; j < work.length; j++) {
                byteHolder[j] = work[j];
            }

            b0 = rand.nextInt(max - min - (segLen + 1)) + min;
            b1 = rand.nextInt(max - min - (segLen + 1)) + min;
            while (b1 >= b0 && b1 <= (b0 + segLen)) {
                b1 = rand.nextInt(max - min - (segLen + 1)) + min;
            }

            for (int k = b0; k < segLen; k++) {
                work[k] = byteHolder[b1 + k];
            }

            for (int l = b0 + segLen; l < work.length; l++) {
                work[l] = byteHolder[l - segLen];
            }
        }
    }
    
    public byte [] addBytes(int segLen, int numA, byte [] work, boolean r) {
        
        byte [] byteHolder;
        byte [] randBytes;
        int b0;
        
        for (int i = 0; i < numA; i++) {
            byteHolder = new byte[work.length];

            for (int j = 0; j < work.length; j++) {
                byteHolder[j] = work[j];
            }

            work = new byte[work.length + segLen];

            min = (int) (work.length * 0.02) + 256;
            max = work.length - 1;

            b0 = rand.nextInt(max - min - (segLen + 1)) + min;
            randBytes = new byte[segLen];
            if (r) {
                rand.nextBytes(randBytes);
            } else {
                for (byte rb : randBytes) {
                    rb = (byte) 0;
                }
            }

            boolean inserted = false;

            for (int k = 0; k < byteHolder.length; k++) {
                if (inserted) {
                    work[k + segLen] = byteHolder[k];
                } else {
                    if (k == b0) {
                        for (int l = 0; l < segLen; l++) {
                            work[k + l] = randBytes[l];
                        }
                    } else {
                        work[k] = byteHolder[k];
                    }
                }
            }
        }
        return work;
    }
    
    public byte [] deleteBytes(int segLen, int numD, byte [] work) {
        
        byte [] byteHolder;
        int b0;
        
        for (int i = 0; i < numD; i++) {
                
            byteHolder = new byte[work.length];

            for (int j = 0; j < work.length; j++) {
                byteHolder[j] = work[j];
            }

            work = new byte[work.length - segLen];

            min = (int) (work.length * 0.02) + 256;
            max = work.length - 1;

            b0 = rand.nextInt(max - min - (segLen + 1)) + min;

            boolean deleted = false;

            for (int k = 0; k < work.length; k++) {
                if (deleted) {
                    work[k] = byteHolder[k + segLen];
                } else {
                    if (k == b0) {
                        deleted = true;
                    } else {
                        work[k] = byteHolder[k];
                    }
                }
            }
        }
        return work;
    }
    
    // ---
    
    public void mutateImage() {
        mutateButton.setEnabled(false);
        
        newByteImage = new byte[byteImage.length];
        for (int i = 0; i < byteImage.length; i++) {
            newByteImage[i] = byteImage[i];
        }
        max = newByteImage.length;
        min = (int) (newByteImage.length * 0.02) + 256;
        
        int segLen;
        
        segLen = rand.nextInt(owIntensitySlider.getValue()) + 8;
        overwriteBytes(segLen, owIterationsSlider.getValue(), newByteImage, owRand.isSelected());
        
        segLen = rand.nextInt(sIntensitySlider.getValue()) + 8;
        swapBytes(segLen, sIterationsSlider.getValue(), newByteImage, byteImage);
        
        segLen = rand.nextInt(mIntensitySlider.getValue()) + 8;
        moveBytes(segLen, mIterationsSlider.getValue(), newByteImage);
        
        segLen = rand.nextInt(aIntensitySlider.getValue()) + 8;
        newByteImage = addBytes(segLen, aIterationsSlider.getValue(), newByteImage, aRand.isSelected());
        
        segLen = rand.nextInt(dIntensitySlider.getValue()) + 8;
        newByteImage = deleteBytes(segLen, dIterationsSlider.getValue(), newByteImage);

        createPreview(newByteImage);
        mutateButton.setEnabled(true);
        saveButton.setEnabled(true);
    }
    
    public void saveBytes(String fname, byte [] bytes) {
        try {
            InputStream isI = new ByteArrayInputStream(bytes);
            BufferedImage buffI = ImageIO.read(isI);
            File outputfile = new File(fname);
            ImageIO.write(buffI, "jpg", outputfile);
            
            //Files.write(Paths.get(fname), bytes);
        } catch (IOException ex) {
            System.out.println(ex.getMessage());
        }
    }
    
    private void mutateButtonPress(java.awt.event.ActionEvent evt) {
        mutateImage();
    }

    private void selectImagePress(java.awt.event.ActionEvent evt) {
        selectAndLoadImage();
    }

    private void savePress(java.awt.event.ActionEvent evt) {
        String newPath = folderPath + "\\" + imageNameField.getText() + ".jpg";
        saveBytes(newPath, newByteImage);
    }

    private void owrSelect(java.awt.event.ActionEvent evt) {
        if (owZero.isSelected()) {
            owRand.setSelected(true);
            owZero.setSelected(false);
        } else {
            owRand.setSelected(false);
            owZero.setSelected(true);
        }
    }

    private void owzSelect(java.awt.event.ActionEvent evt) {
        if (owRand.isSelected()) {
            owRand.setSelected(false);
            owZero.setSelected(true);
        } else {
            owRand.setSelected(true);
            owZero.setSelected(false);
        }
    }

    private void arSelect(java.awt.event.ActionEvent evt) {
        if (aZero.isSelected()) {
            aRand.setSelected(true);
            aZero.setSelected(false);
        } else {
            aRand.setSelected(false);
            aZero.setSelected(true);
        }
    }

    private void azSelect(java.awt.event.ActionEvent evt) {
        if (aRand.isSelected()) {
            aRand.setSelected(false);
            aZero.setSelected(true);
        } else {
            aRand.setSelected(true);
            aZero.setSelected(false);
        }
    }

    private void resetButton(java.awt.event.ActionEvent evt) {
        owIntensitySlider.setValue(0);
        aIntensitySlider.setValue(0);
        sIntensitySlider.setValue(0);
        dIntensitySlider.setValue(0);
        mIntensitySlider.setValue(0);
        owIterationsSlider.setValue(0);
        aIterationsSlider.setValue(0);
        sIterationsSlider.setValue(0);
        dIterationsSlider.setValue(0);
        mIterationsSlider.setValue(0);
        aRand.setSelected(true);
        owRand.setSelected(true);
        aZero.setSelected(false);
        owZero.setSelected(false);
    }

    public static void main(String args[]) {
        
        try {
            javax.swing.UIManager.setLookAndFeel(javax.swing.UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
            System.out.println("Problem setting up window.");
        }

        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new Main().setVisible(true);
            }
        });
    }

    private javax.swing.JLabel aIntLabel;
    private javax.swing.JSlider aIntensitySlider;
    private javax.swing.JLabel aIterLabel;
    private javax.swing.JSlider aIterationsSlider;
    private javax.swing.JLabel aLabel;
    private javax.swing.JRadioButton aRand;
    private javax.swing.JRadioButton aZero;
    private javax.swing.JLabel dIntLabel;
    private javax.swing.JSlider dIntensitySlider;
    private javax.swing.JLabel dIterLabel;
    private javax.swing.JSlider dIterationsSlider;
    private javax.swing.JLabel dLabel;
    private javax.swing.JButton mutateButton;
    private javax.swing.JTextField imageNameField;
    private javax.swing.JPanel imagePanel;
    private javax.swing.JLabel mIntLabel;
    private javax.swing.JSlider mIntensitySlider;
    private javax.swing.JLabel mIterLabel;
    private javax.swing.JSlider mIterationsSlider;
    private javax.swing.JLabel mLabel;
    private javax.swing.JLabel owIntLabel;
    private javax.swing.JSlider owIntensitySlider;
    private javax.swing.JLabel owIterLabel;
    private javax.swing.JSlider owIterationsSlider;
    private javax.swing.JLabel owLabel;
    private javax.swing.JRadioButton owRand;
    private javax.swing.JRadioButton owZero;
    private javax.swing.JSeparator paramSep0;
    private javax.swing.JSeparator paramSep1;
    private javax.swing.JSeparator paramSep2;
    private javax.swing.JSeparator paramSep3;
    private javax.swing.JSeparator paramSep4;
    private javax.swing.JButton resetParamsButton;
    private javax.swing.JLabel sIntLabel;
    private javax.swing.JSlider sIntensitySlider;
    private javax.swing.JLabel sIterLabel;
    private javax.swing.JSlider sIterationsSlider;
    private javax.swing.JLabel sLabel;
    private javax.swing.JButton saveButton;
    private javax.swing.JLabel saveLabel;
    private javax.swing.JSeparator screenSep;
    private javax.swing.JButton selectImageButton;
}
