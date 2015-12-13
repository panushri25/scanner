

int dabba=30;  //change this to change the size of pixel box averaged                    
PImage img;
float rval=0,bval=0,gval=0;

void setup() { 
 img = loadImage("f.jpg"); // Load the original image
 size(2*img.width,img.height);
 noLoop();
}

void draw() {
 image(img, 0, 0); // Displays the image from point (0,0) 
 img.loadPixels();
 // Create an opaque image of the same size as the original
 PImage avImg = createImage(img.width, img.height, RGB);
 // Loop through every pixel in the image.
 for (int y = dabba; y < img.height-dabba; y++) { // Skip top and bottom edges
   for (int x = dabba; x < img.width-dabba; x++) { // Skip left and right edges
//      float sum = 0; // Kernel sum for this pixel
     for (int ky = -dabba; ky <= dabba; ky++) {
     for (int kx = -dabba; kx <= dabba; kx++) {
         // Calculate the adjacent pixel for this kernel point
         int pos = (y + ky)*img.width + (x + kx);
         // Image is grayscale, red/green/blue are identical
         float valr = red(img.pixels[pos]);
         float valb = blue(img.pixels[pos]);
         float valg = green(img.pixels[pos]);
         rval+=valr;
         bval+=valb;
         gval+=valg;
         // Multiply adjacent pixels based on the kernel values
         //sum += kernel[ky+1][kx+1] * val;
       }
     }
     
 rval/=((2*dabba+1)*(2*dabba+1));
 bval/=((2*dabba+1)*(2*dabba+1));
 gval/=((2*dabba+1)*(2*dabba+1));
 avImg.pixels[y*img.width + x] = color(rval, bval, gval);
     rval=0;
     gval=0;
     bval=0;
   }
 }
 // State that there are changes to avImg.pixels[]
 avImg.updatePixels();
 image(avImg, width/2, 0); // Draw the new image
 save("g3.jpg");
}
