#include <iostream>
#include <cmath>
#include "dip.h"

#define UNSHARP(src1, src2, ratio) (src1 + (src1 - src2) * ratio)

#ifdef DEBUG
void Display(vector <vector <int>> & orgPM) {
  const uint16_t height = orgPM.size();
  const uint16_t width = orgPM[0].size();

  for (int row = 0; row < height; row++) { 
    for (int col = 0; col < width; col++) { 
        cout << setw(5) << left << orgPM[row][col]; 
    }     
    cout << "\n"; 
  }
}
#endif

void AddCol(PixelMatrix & orgPM, const PixelVector & column, uint16_t pos) {
  const uint16_t height = orgPM.size();
  const uint16_t width = orgPM[0].size();
  
	if (pos < 0 || pos > width) {
		std::cerr << "[ERROR] Invalid position.\n";
	}
	if (column.size() != height) {
		std::cerr << "[ERROR] Invalid column.\n";
	}

	// Insert the column at the specified position
	for (uint16_t i = 0; i < height; i++) {
	    orgPM[i].insert(orgPM[i].begin() + pos, column[i]);
	}
};

void AddRow(PixelMatrix & orgPM, const PixelVector & row, uint16_t pos) {
  const uint16_t height = orgPM.size();
  const uint16_t width = orgPM[0].size();
  
	if (pos < 0 || pos > height) {
		std::cerr << "[ERROR] Invalid position.\n";
	}
	if (row.size() != width) {
		std::cerr << "[ERROR] Invalid row.\n";
	}

	// Insert the row at the specified position
	orgPM.insert(orgPM.begin() + pos, row);
};

PixelMatrix Padding(const PixelMatrix & orgPM, const uint16_t pad_width, const char pad_type) {
  uint16_t height = orgPM.size();
  uint16_t width  = orgPM[0].size();

  auto resPM(orgPM);
  resPM = orgPM;

  uint16_t temp = 726;

  switch(pad_type) {
    case 'e': // Pads with the edge values of array.
      for (uint16_t row = 0; row < height; row++) {
        for (uint16_t i = 0; i < pad_width; i++) {
          resPM[row].insert(resPM[row].begin(), orgPM[row][0]);
          resPM[row].insert(resPM[row].end(), orgPM[row][width-1]);
        }
      }
      width += pad_width * 2;
      for (uint16_t col = 0; col < pad_width; col++) {
        resPM.insert(resPM.end(), resPM[height-1]);
        resPM.insert(resPM.begin(), resPM[0]);
        height += 2;
      }
      break;
    default: // Zero padding.
      PixelVector insertCol(height, Pixel<int>());
      PixelVector insertRow(width + pad_width * 2, Pixel<int>());

      for (uint16_t col = 0; col < pad_width; col++) {
         AddCol(resPM, insertCol, width);
         AddCol(resPM, insertCol, 0);
         width += 2;
      }
      for (uint16_t row = 0; row < pad_width; row++) {
         AddRow(resPM, insertRow, height);
         AddRow(resPM, insertRow, 0);
         height += 2;
      }
  }

  return resPM;
};

float dnorm(int pos, float sd, float mu = 0) {
  return 1 / (sqrt(2 * M_PI) * sd) * exp(-pow(((float)pos - mu) / sd, 2) / 2);
}

PixelMatrix GaussianBlur(const PixelMatrix & orgPM, uint16_t kernelSize, float sd) {
  if (kernelSize % 2 == 0) {
    std::cerr << "[ERROR] Kernel size must be odd sized.\n";
    exit(1);
  }

  float * kernel1D = (float *)malloc(sizeof(float) * kernelSize);
  int offset = kernelSize / 2;
  const uint16_t height = orgPM.size();
  const uint16_t width = orgPM[0].size();

  std::vector <std::vector <Pixel<float>>> tempPM;
  PixelMatrix resPM(height - kernelSize + 1, PixelVector (width - kernelSize + 1));

  float sum = 0;
  for (uint16_t i = 0; i < kernelSize; i++) {
    kernel1D[i] = dnorm((int)(-offset+i), sd);
    sum += kernel1D[i];
  }
  for (uint16_t i = 0; i < kernelSize; i++) {
    kernel1D[i] /= sum;
  }

  for (uint16_t row = 0; row < (height - kernelSize + 1); row++) {
    std::vector <Pixel<float>> row_data;
    for (uint16_t col = 0; col < width; col++) {
      Pixel<float> pixel;

      for (uint16_t i = 0; i < kernelSize; i++) {
        pixel.red   += (float)orgPM[row + i][col].red * kernel1D[i];
        pixel.green += (float)orgPM[row + i][col].green * kernel1D[i];
        pixel.blue  += (float)orgPM[row + i][col].blue * kernel1D[i];
      }
      row_data.push_back(pixel);
    }
    tempPM.push_back(row_data);
  }
  for (uint16_t col = 0; col < (width - kernelSize + 1); col++) {
    for (uint16_t row = 0; row < (height - kernelSize + 1); row++) {
      Pixel<int> & pixel = resPM[row][col];
      float red, green, blue;
      red = green = blue = 0;

      for (uint16_t i = 0; i < kernelSize; i++) {
        red   += tempPM[row][col + i].red * kernel1D[i];
        green += tempPM[row][col + i].green * kernel1D[i];
        blue  += tempPM[row][col + i].blue * kernel1D[i];
      }
      pixel.red   = (int)red;
      pixel.green = (int)green;
      pixel.blue  = (int)blue;
    }
  }
  free(kernel1D);

  return resPM;
}

PixelMatrix UnsharpMask(const PixelMatrix & orgPM, const uint16_t ratio) {
  const uint16_t height = orgPM.size();
  const uint16_t width  = orgPM[0].size();
  const uint16_t kernelSize = 9;
  const uint16_t sd = 10;

  PixelMatrix blurPM, resPM;
  blurPM = Padding(orgPM, kernelSize / 2, 'e');
  blurPM = GaussianBlur(blurPM, kernelSize, sd);

  for (uint16_t row = 0; row < height; row++) {
    PixelVector row_data;
    for (uint16_t col = 0; col < width; col++) {
      Pixel<int> pixels;
      pixels.red    = (int)CLAMP(UNSHARP((float)orgPM[row][col].red, blurPM[row][col].red, ratio));
      pixels.green  = (int)CLAMP(UNSHARP((float)orgPM[row][col].green, blurPM[row][col].green, ratio));
      pixels.blue   = (int)CLAMP(UNSHARP((float)orgPM[row][col].blue, blurPM[row][col].blue, ratio));

      row_data.push_back(pixels);
    }
    resPM.push_back(row_data);
  }

  return resPM;
}

PixelMatrix HistEqual_RGB(const PixelMatrix & orgPM) {
  PixelMatrix resPixelMatrix;
  HSLMatrix orgHSLMatrix;

  // int histogram[256] = {0};
  // int mappingFunction[256] = {0};
  PixelVector histogram(256, Pixel<int>());
  PixelVector mappingFunction(256, Pixel<int>());

  const uint16_t height = orgPM.size();
  const uint16_t width = orgPM[0].size();
  const uint32_t totalPixel = orgPM.size() * orgPM[0].size();

  Pixel<uint32_t> cdf;

  for (uint16_t row = 0; row < height; row++) {
    std::vector <HSL> row_data;
    for (uint16_t col = 0; col < width; col++) {
      HSL pixel;

      pixel.fromRGB(orgPM[row][col]);
      
      row_data.push_back(pixel);
    }
    orgHSLMatrix.push_back(row_data);
  }

  // =================== write file ==================
  #ifdef DEBUG
  ofstream outdata;
  outdata.open("lightness.dat", ofstream::out | ofstream::trunc);
  if( !outdata ) { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
   }
  #endif


  for (uint16_t row = 0; row < height; row++) {
    for (uint16_t col = 0; col < width; col++) {
      histogram[orgPM[row][col].red].red++;
      histogram[orgPM[row][col].green].green++;
      histogram[orgPM[row][col].blue].blue++;
      // #ifdef DEBUG
      // outdata << (int)(orgHSLMatrix[row][col].lightness * 255) << "\n";
      // #endif
    }
  }


  for (uint16_t i = 0; i < 256; i++) {
    cdf.red   += histogram[i].red;
    cdf.green += histogram[i].green;
    cdf.blue  += histogram[i].blue;

    mappingFunction[i].red    = round((float)cdf.red / totalPixel * 255);
    mappingFunction[i].green  = round((float)cdf.green / totalPixel * 255);
    mappingFunction[i].blue   = round((float)cdf.blue / totalPixel * 255);
  }

  for (uint16_t row = 0; row < height; row++) {
    std::vector <Pixel<int>> row_data;
    for (uint16_t col = 0; col < width; col++) {
      Pixel<int> pixel;

      pixel.red = mappingFunction[orgPM[row][col].red].red;
      pixel.green = mappingFunction[orgPM[row][col].green].green;
      pixel.blue = mappingFunction[orgPM[row][col].blue].blue;
      #ifdef DEBUG
      outdata << mappingFunction[(int)(orgHSLMatrix[row][col].lightness * 255)] << "\n";
      #endif

      row_data.push_back(pixel);
    }
    resPixelMatrix.push_back(row_data);
  }

  #ifdef DEBUG
  outdata.close();
  #endif
  // =================== write file ==================
  return resPixelMatrix;
}

PixelMatrix HistEqual_HSL(const PixelMatrix & orgPixelMatrix) {
  PixelMatrix resPixelMatrix;
  HSLMatrix orgHSLMatrix;

  int histogram[256] = {0};
  int mappingFunction[256] = {0};

  const uint16_t height = orgPixelMatrix.size();
  const uint16_t width = orgPixelMatrix[0].size();
  const uint32_t totalPixel = orgPixelMatrix.size() * orgPixelMatrix[0].size();

  uint32_t cdf = 0;

  for (uint16_t row = 0; row < height; row++) {
    std::vector <HSL> row_data;
    for (uint16_t col = 0; col < width; col++) {
      HSL pixel;

      pixel.fromRGB(orgPixelMatrix[row][col]);
      
      row_data.push_back(pixel);
    }
    orgHSLMatrix.push_back(row_data);
  }

  // =================== write file ==================
  #ifdef DEBUG
  ofstream outdata;
  outdata.open("lightness.dat", ofstream::out | ofstream::trunc);
  if( !outdata ) { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
   }
  #endif


  for (uint16_t row = 0; row < height; row++) {
    for (uint16_t col = 0; col < width; col++) {
      histogram[(int)(orgHSLMatrix[row][col].lightness * 255)]++;
      // #ifdef DEBUG
      // outdata << (int)(orgHSLMatrix[row][col].lightness * 255) << "\n";
      // #endif
    }
  }


  for (uint16_t i = 0; i < 256; i++) {
    cdf += histogram[i];
    mappingFunction[i] = round((float)cdf / totalPixel * 255);
  }

  for (uint16_t row = 0; row < height; row++) {
    std::vector <Pixel<int>> row_data;
    for (uint16_t col = 0; col < width; col++) {
      HSL pixel;

      pixel.hue = orgHSLMatrix[row][col].hue;
      pixel.saturation = orgHSLMatrix[row][col].saturation;
      pixel.lightness = (float)mappingFunction[(int)(orgHSLMatrix[row][col].lightness * 255)] / 255;
      #ifdef DEBUG
      outdata << mappingFunction[(int)(orgHSLMatrix[row][col].lightness * 255)] << "\n";
      #endif

      row_data.push_back(pixel.toRGB());
    }
    resPixelMatrix.push_back(row_data);
  }

  #ifdef DEBUG
  outdata.close();
  #endif
  // =================== write file ==================
  return resPixelMatrix;
}

PixelMatrix MinMaxStretching(const PixelMatrix & orgPM) {  
  PixelMatrix resPM;
  HSLMatrix orgHSLMatrix;

  float minVal = 1000;
  float maxVal = 0;
  float delta = 0;
  float magic = 0.3;

  int histogram[256] = {0};
  int mappingFunction[256] = {0};

  const uint16_t height = orgPM.size();
  const uint16_t width = orgPM[0].size();
  const uint32_t totalPixel = orgPM.size() * orgPM[0].size();

  uint32_t cdf = 0;

  for (uint16_t row = 0; row < height; row++) {
    std::vector <HSL> row_data;
    for (uint16_t col = 0; col < width; col++) {
      HSL pixel;

      pixel.fromRGB(orgPM[row][col]);
      
      minVal = pixel.lightness < minVal ? pixel.lightness : minVal;
      maxVal = pixel.lightness > maxVal ? pixel.lightness : maxVal;

      row_data.push_back(pixel);
    }
    orgHSLMatrix.push_back(row_data);
  }

  delta = maxVal - minVal;

  for (uint16_t row = 0; row < height; row++) {
    PixelVector row_data;
    for (uint16_t col = 0; col < width; col++) {
      HSL pixel;

      pixel.hue = orgHSLMatrix[row][col].hue;
      pixel.saturation = orgHSLMatrix[row][col].saturation;
      pixel.lightness = MIN((orgHSLMatrix[row][col].lightness + magic) / delta, 1);

      row_data.push_back(pixel.toRGB());
    }
    resPM.push_back(row_data);
  }

  return resPM;
}

HSLMatrix RGB2HSL(const PixelMatrix & orgPixelMatrix) {
  PixelMatrix resPixelMatrix;
  HSLMatrix orgHSLMatrix;

  const uint16_t height = orgPixelMatrix.size();
  const uint16_t width = orgPixelMatrix[0].size();
  const uint32_t totalPixel = orgPixelMatrix.size() * orgPixelMatrix[0].size();

  for (uint16_t row = 0; row < height; row++) {
    std::vector <HSL> row_data;
    for (uint16_t col = 0; col < width; col++) {
      HSL pixel;
      
      pixel.fromRGB(orgPixelMatrix[row][col]);

      row_data.push_back(pixel);
    }
    orgHSLMatrix.push_back(row_data);
  }

  return orgHSLMatrix;
}

PixelMatrix HSL2RGB(const HSLMatrix & orgHSLMatrix) {
  PixelMatrix orgPixelMatrix;

  const uint16_t height = orgHSLMatrix.size();
  const uint16_t width = orgHSLMatrix[0].size();
  const uint32_t totalPixel = orgHSLMatrix.size() * orgHSLMatrix[0].size();

  for (uint16_t row = 0; row < height; row++) {
    std::vector <Pixel<int>> row_data;
    for (uint16_t col = 0; col < width; col++) {
      HSL pixel;

      pixel = orgHSLMatrix[row][col];
      row_data.push_back(pixel.toRGB());
    }
    orgPixelMatrix.push_back(row_data);
  }

  return orgPixelMatrix;
}

void quickSort(std::vector <int> & array, int low, int high) {
    int i = low;
    int j = high;
    int pivot = array[(i + j) / 2];
    int temp;

    while (i <= j)
    {
        while (array[i] < pivot)
            i++;
        while (array[j] > pivot)
            j--;
        if (i <= j)
        {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }
    if (j > low)
        quickSort(array, low, j);
    if (i < high)
        quickSort(array, i, high);
}

PixelMatrix MedianFilter(const PixelMatrix & orgPM, const uint16_t kernelSize) {
  const uint16_t height = orgPM.size();
  const uint16_t width  = orgPM[0].size();
  const uint16_t kernelLen = pow(kernelSize, 2);
  const uint16_t median = kernelLen / 2 + 1;

  PixelMatrix padPM, resPM;
  padPM = Padding(orgPM, kernelSize / 2, 'e');

  for (uint16_t row = 0; row < height; row++) {
    PixelVector row_data;
    for (uint16_t col = 0; col < width; col++) {
      std::vector <int> rA, gA, bA;
      for (uint16_t i = 0; i < kernelSize; i++) {
        for (uint16_t j = 0; j < kernelSize; j++) {
          rA.push_back(padPM[row+i][col+j].red);
          gA.push_back(padPM[row+i][col+j].green);
          bA.push_back(padPM[row+i][col+j].blue);
        }
      }
      quickSort(rA, 0, kernelLen);
      quickSort(gA, 0, kernelLen);
      quickSort(bA, 0, kernelLen);
      row_data.push_back(Pixel<int>(rA[median], gA[median], bA[median], 0));
    }
    resPM.push_back(row_data);
  }
  
  return resPM;
}
