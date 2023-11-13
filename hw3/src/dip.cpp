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

void AddCol(PixelMatrix &orgPM, const PixelVector &column, uint16_t pos)
{
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

void AddRow(PixelMatrix &orgPM, const PixelVector &row, uint16_t pos)
{
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

PixelMatrix Padding(const PixelMatrix &orgPM, const uint16_t pad_width, const char pad_type)
{
	uint16_t height = orgPM.size();
	uint16_t width = orgPM[0].size();

	auto resPM(orgPM);
	resPM = orgPM;

	switch (pad_type)
	{
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

PixelMatrix AdjustLightness(const PixelMatrix & orgPM, const float & value) {
  	const uint16_t height = orgPM.size();
  	const uint16_t width = orgPM[0].size();

	PixelMatrix dstPM;
  	HSLMatrix srcHSLMatrix;

	Pixel <float> maxValue;

  	for (uint16_t row = 0; row < height; row++) {
  	  std::vector <HSL> row_data;
  	  for (uint16_t col = 0; col < width; col++) {
  	    HSL pixel;

  	    pixel.fromRGB(orgPM[row][col]);
		pixel.lightness += value;
		pixel.lightness = MIN(pixel.lightness, 1);

		maxValue.c2 = MAX(pixel.saturation, maxValue.c2);
	
  	    row_data.push_back(pixel);
  	  }
  	  srcHSLMatrix.push_back(row_data);
  	}

  	for (uint16_t row = 0; row < height; row++) {
  	  PixelVector row_data;
  	  for (uint16_t col = 0; col < width; col++) {
  	    HSL pixel;

		pixel.hue = srcHSLMatrix[row][col].hue;
		pixel.saturation = srcHSLMatrix[row][col].saturation;
		pixel.lightness = srcHSLMatrix[row][col].lightness;

		pixel.saturation = MIN(maxValue.c2, pixel.saturation + value);

		row_data.push_back(pixel.toRGB());
	  }
	  dstPM.push_back(row_data);
	}
	return dstPM;
}

PixelMatrix RGB2YCbCr(const PixelMatrix &srcPM)
{
	const uint16_t height = srcPM.size();
  	const uint16_t width = srcPM[0].size();

  	PixelMatrix dstPM(height, PixelVector (width));

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int red   = srcPM[row][col].c1;
			int green = srcPM[row][col].c2;
			int blue  = srcPM[row][col].c3;
			dstPM[row][col].c1 = (int)((YCbCrYRI * red + YCbCrYGI * green + YCbCrYBI * blue + HalfShiftValue) >> Shift);
			dstPM[row][col].c2 = (int)(128 + ((YCbCrCbRI * red + YCbCrCbGI * green + YCbCrCbBI * blue + HalfShiftValue) >> Shift));
			dstPM[row][col].c3 = (int)(128 + ((YCbCrCrRI * red + YCbCrCrGI * green + YCbCrCrBI * blue + HalfShiftValue) >> Shift));
		}
	}
	return dstPM;
}

PixelMatrix YCbCr2RGB(const PixelMatrix &srcPM)
{
	const uint16_t height = srcPM.size();
  	const uint16_t width = srcPM[0].size();

  	PixelMatrix dstPM(height, PixelVector (width));

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int Y   = srcPM[row][col].c1;
			int Cb  = srcPM[row][col].c2 - 128;
			int Cr  = srcPM[row][col].c3 - 128;
			int red   = Y + ((RGBRCrI * Cr + HalfShiftValue) >> Shift);
			int green = Y + ((RGBGCbI * Cb + RGBGCrI * Cr + HalfShiftValue) >> Shift);
			int blue  = Y + ((RGBBCbI * Cb + HalfShiftValue) >> Shift);
			if (red > 255) red = 255; else if (red < 0) red = 0;
			if (green > 255) green = 255; else if (green < 0) green = 0;
			if (blue > 255) blue = 255; else if (blue < 0) blue = 0;
			dstPM[row][col].c1 = red;
			dstPM[row][col].c2 = green;
			dstPM[row][col].c3 = blue;
		}
	}
	return dstPM;
}

PixelMatrix Rect(const PixelMatrix &srcPM, const uint16_t startX, const uint16_t startY, const uint16_t cropW, const uint16_t cropH)
{
	PixelMatrix dstPM;

	for (uint16_t row = startY; row < startY + cropH; row++)
	{
		PixelVector row_data;
		for (uint16_t col = startX; col < startX + cropW; col++)
		{
			row_data.push_back(Pixel<int>(srcPM[row][col].c1, srcPM[row][col].c2, srcPM[row][col].c3, srcPM[row][col].c4));
		}
		dstPM.push_back(row_data);
	}

	return dstPM;
}

std::vector <double> GlobalMean(const PixelMatrix & srcPM) {
  const uint16_t height = srcPM.size();
  const uint16_t width  = srcPM[0].size();

  std::vector <double> dstVec(4, 0.);

  for (uint16_t row = 0; row < height; row++) {
    for (uint16_t col = 0; col < width; col++) {
      dstVec[0] += srcPM[row][col].c1;
      dstVec[1] += srcPM[row][col].c2;
      dstVec[2] += srcPM[row][col].c3;
      dstVec[3] += srcPM[row][col].c4;
    }
  }

  dstVec[0] /= height * width; 
  dstVec[1] /= height * width; 
  dstVec[2] /= height * width; 
  dstVec[3] /= height * width; 

  return dstVec;
}

template<typename T>
inline T sign(T const & input) {
	return input >= 0 ? 1 : -1;
}

PixelMatrix AutomaticWhiteBalanceMethod(const PixelMatrix &srcPM)
{
	const uint16_t height = srcPM.size();
	const uint16_t width = srcPM[0].size();

	// RGB-> YCbCr
	PixelMatrix input = RGB2YCbCr(srcPM);
	std::vector<std::vector<uchar_t>> mark(height, std::vector<uchar_t>(width));

	int sum = 0;

	for (uint16_t row = 0; row < height; row += 100)
	{
		for (uint16_t col = 0; col < width; col += 100)
		{
			if (row + 100 < height && col + 100 < width)
			{
				PixelMatrix temp = Rect(input, col, row, 100, 100);

				// 計算patch平均值
				std::vector<double> globalMean = GlobalMean(temp);
				double dr = 0, db = 0;
				for (uint16_t x = 0; x < 100; x++)
				{
					for (uint16_t y = 0; y < 100; y++)
					{
						dr += std::pow(std::abs(temp[y][x].c2 - globalMean[1]), 2);
						db += std::pow(std::abs(temp[y][x].c3 - globalMean[2]), 2);
					}
				}
				dr /= 10000;
				db /= 10000;
				double cr_left_criteria 	= 1.5 * globalMean[1] + dr * sign(globalMean[1]);
				double cr_right_criteria 	= 1.5 * dr;
				double cb_left_criteria 	= globalMean[2] + db * sign(globalMean[2]);
				double cb_right_criteria 	= 1.5 * db;
				for (uint16_t x = 0; x < 100; x++)
				{
					for (uint16_t y = 0; y < 100; y++)
					{
						uchar_t cr = temp[y][x].c2;
						uchar_t cb = temp[y][x].c3;

						// 判斷是否為候選參考白點
						if (((int)cr - cb_left_criteria) < cb_right_criteria && ((int)cb - cr_left_criteria) < cr_right_criteria)
						{
							sum++;
							mark[row + y][col + x] = 1;
						}
						else
						{
							mark[row + y][col + x] = 0;
						}
					}
				}
			}
		}
	}

	int Threshold = 0;
	int Ymax = 0;
	uint16_t Light[256] = {0};
	// 統計參考白點亮度值
	for (uint16_t row = 0; row < height; row++)
	{
		for (uint16_t col = 0; col < width; col++)
		{
			if (mark[row][col] == 1)
			{
				Light[(int)(input[row][col].c1)]++;
			}
			Ymax = MAX(Ymax, (int)(input[row][col].c1));
		}
	}
	int sum2 = 0;
	for (int i = 255; i >= 0; i--) {
		sum2 += Light[i];
		// 取前10%的near-white region的亮度值
		if (sum2 >= sum * 0.1)
		{
			Threshold = i;
			break;
		}
	}
	double blue		= 0;
	double green 	= 0;
	double red 		= 0;
	uint32_t cnt2	= 0;
	for (uint16_t row = 0; row < height; row++)
	{
		for (uint16_t col = 0; col < width; col++)
		{	// RGB通道增益只參考參考白點
			if (mark[row][col] == 1 && (int)(input[row][col].c1) >= Threshold)
			{
				red		+= 1.0 * srcPM[row][col].c1;
				green 	+= 1.0 * srcPM[row][col].c2;
				blue 	+= 1.0 * srcPM[row][col].c3;
				cnt2++;
			}
		}
	}
	blue 	/= cnt2;
	green 	/= cnt2;
	red 	/= cnt2;
	PixelMatrix dstPM(height, PixelVector (width));
	double maxY = Ymax;
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			// 將RGB通道增益應用到整張影像
			int R = (int)(maxY * srcPM[row][col].c1 / red);
			int G = (int)(maxY * srcPM[row][col].c2 / green);
			int B = (int)(maxY * srcPM[row][col].c3 / blue);
			if (B > 255) B = 255; else if (B < 0) B = 0;
			if (G > 255) G = 255; else if (G < 0) G = 0;
			if (R > 255) R = 255; else if (R < 0) R = 0;
			dstPM[row][col].c1 = R;
			dstPM[row][col].c2 = G;
			dstPM[row][col].c3 = B;
		}
	}
	return dstPM;
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

// Function to calculate percentile for a given vector
std::vector <uint16_t> calculatePercentile(const PixelMatrix & srcPM, std::vector <uint16_t> & percentile) {
    // Flatten the 3D vector into a 1D vector
    std::vector <int> flattenedData;
	std::vector <uint16_t> dstVec;

	const uint16_t height = srcPM.size();
	const uint16_t width = srcPM[0].size();

	for (uint16_t row = 0; row < height; row++) {
		for (uint16_t col = 0; col < width; col++) {
			flattenedData.push_back(srcPM[row][col].c1);
			flattenedData.push_back(srcPM[row][col].c2);
			flattenedData.push_back(srcPM[row][col].c3);
		}
	}

    // Sort the flattened data vector
	quickSort(flattenedData, 0, flattenedData.size());

    // Calculate the index corresponding to the given percentile
	for (uint16_t i = 0; i < percentile.size(); i++) {
    	uint32_t index = (double)percentile[i] / 100 * flattenedData.size();
		dstVec.push_back(flattenedData[index]);
	}

    // Return the value at the calculated index
    return dstVec;
}

PixelMatrix RescaleIntensity(const PixelMatrix & srcPM, const uint16_t newMax, const uint16_t newMin)
{
	const uint16_t height = srcPM.size();
	const uint16_t width = srcPM[0].size();
	const uint16_t newDelta = newMax - newMin;

	Pixel <uint16_t> oldMax, oldMin(10000, 10000, 10000, 10000);
	PixelMatrix dstPM;
	// 找出整張影像RGB最大及最小值
	for (uint16_t row = 0; row < height; row++) {
		for (uint16_t col = 0; col < width; col++) {
			oldMax.c1 = MAX(srcPM[row][col].c1, oldMax.c1);
			oldMax.c2 = MAX(srcPM[row][col].c2, oldMax.c2);
			oldMax.c3 = MAX(srcPM[row][col].c3, oldMax.c3);
			
			oldMin.c1 = MIN(srcPM[row][col].c1, oldMin.c1);
			oldMin.c2 = MIN(srcPM[row][col].c2, oldMin.c2);
			oldMin.c3 = MIN(srcPM[row][col].c3, oldMin.c3);
		}
	}
	// 計算原始影像最大及最小值之間的差
	Pixel <uint16_t> oldDelta (oldMax.c1 - oldMin.c1,
								oldMax.c2 - oldMin.c2,
								oldMax.c3 - oldMin.c3,
								0);

	for (uint16_t row = 0; row < height; row++) {
		PixelVector row_data;
		for (uint16_t col = 0; col < width; col++) {
			Pixel <int> pixel;
			// 線性轉換，將舊的值映射到新的range
			pixel.c1 = (srcPM[row][col].c1 - oldMin.c1) * newDelta / oldDelta.c1 + newMin;
			pixel.c2 = (srcPM[row][col].c2 - oldMin.c2) * newDelta / oldDelta.c2 + newMin;
			pixel.c3 = (srcPM[row][col].c3 - oldMin.c3) * newDelta / oldDelta.c3 + newMin;

			row_data.push_back(pixel);
		}
		dstPM.push_back(row_data);
	}
	return dstPM;
}

PixelMatrix GrayWorldWB(const PixelMatrix & srcPM) {
	const uint16_t height = srcPM.size();
	const uint16_t width = srcPM[0].size();

	std::vector <std::vector <int>> rPM (height, std::vector <int> (width));
	std::vector <std::vector <int>> gPM (height, std::vector <int> (width));
	std::vector <std::vector <int>> bPM (height, std::vector <int> (width));

	PixelMatrix dstPM;

	for (uint16_t row = 0; row < height; row++) {
		for (uint16_t col = 0; col < width; col++) {
			rPM[row][col] = srcPM[row][col].c1;
			gPM[row][col] = srcPM[row][col].c2;
			bPM[row][col] = srcPM[row][col].c3;
		}
	}

	std::vector <double> globalMean = GlobalMean(srcPM);
	float Mean = (globalMean[0] + globalMean[1] + globalMean[2]) / 3;
	float rR = Mean / globalMean[0];
	float gR = Mean / globalMean[1];
	float bR = Mean / globalMean[2];

	for (uint16_t row = 0; row < height; row++) {
		PixelVector row_data;
		for (uint16_t col = 0; col < width; col++) {
			Pixel <int> pixel;

			pixel.c1 = CLAMP(rPM[row][col] * rR);
			pixel.c2 = CLAMP(gPM[row][col] * gR);
			pixel.c3 = CLAMP(bPM[row][col] * bR);

			row_data.push_back(pixel);
		}
		dstPM.push_back(row_data);
	}
	return dstPM;
}