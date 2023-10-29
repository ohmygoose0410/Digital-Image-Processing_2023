#include <iostream>
#include <fstream>
#include "bitmap.h"

typedef unsigned char uchar_t;
typedef unsigned int uint32_t;
typedef unsigned short int uint16_t;
typedef signed int int32_t;

const int MIN_VAL		= 0;
const int MAX_VAL		= 255;
const int MAGIC_NUMBER	= 2;

struct bmp_magic
{
	uchar_t magic[MAGIC_NUMBER];	// 辨識BMP檔案
};

struct bmp_header_format
{
	uint32_t file_size;				// 整包檔案大小
	uint16_t creator1;				// 保留
	uint16_t creator2;				// 保留
	uint32_t bmp_offset;			// 點陣圖資料的位置偏移
};

struct dib_header_format
{
  uint32_t header_size; 			// Info Header 總體長度 (4 Bytes)
  int32_t width;					// 點陣圖寬度 (4 Bytes)
  int32_t height;					// 點陣圖高度 (4 Bytes)
  uint16_t num_planes;				// 色彩平面數，只有1為有效值 (2 Bytes)
  uint16_t bits_per_pixel;			// 每個像素所佔的位元數，也就是色深 (2 Bytes)
  uint32_t compression;				// 所使用的壓縮方法 (4 Bytes)
  uint32_t bmp_byte_size;			// 圖像大小，指原始點陣圖資料的大小 (4 Bytes)
  int32_t hres;						// 水平解析度 (4 Bytes)
  int32_t vres;						// 垂直解析度 (4 Bytes)
  uint32_t num_colors;				// 調色盤顏色數，為0表示顏色數為預設的2^(色深)個 (4 Bytes)
  uint32_t num_important_colors;	// 重要顏色數，為0表示所有顏色都是重要的 (4 Bytes)
};

void BMP::Read(std::string filename) {
	std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary);
	// 清空buffer
    for(int i=0; i<pixels.size(); i++) {
        pixels[i].clear();
    }
    pixels.clear();

	if (file.fail()) {
		std::cerr << "[ERROR] Error during read operation.\n";
	}
	else {
		// 讀取magic number
		bmp_magic magic;
		file.read((char*)(&magic), sizeof(magic));

		if (magic.magic[0] != 'B' || magic.magic[1] != 'M') {
			std::cerr << "[ERROR] It's not a valid bmp file.\n";
		}
		else {
			// 讀取bmp header
			bmp_header_format bmp_header;
			file.read((char*)(&bmp_header), sizeof(bmp_header));

			// 讀取dib header
			dib_header_format dib_header;
			file.read((char*)(&dib_header), sizeof(dib_header));

			// 檢查bmp使否顛倒儲存
			bool flip = true;
			if (dib_header.height < 0) {
				flip = false;
				dib_header.height = -dib_header.height;
			}

			// 檢查使用3個channel，還是4個channel
			switch (dib_header.bits_per_pixel) {
			case 24:
				existalpha = false;
				break;
			case 32:
				existalpha = true;
				break;
			default:
				std::cerr << "[ERROR] " << filename << " uses " << dib_header.bits_per_pixel
				<< "bits per pixel. BMP only supports 24bit or 32bit.\n";
				break;
			}

			if (dib_header.compression != 0) {
				std::cerr << "[ERROR] Not support uncompressed images.\n";
			}
			// offset至pixel matrix位置
			file.seekg(bmp_header.bmp_offset);

			// 讀取pixel matrix資料
			for (int row = 0; row < dib_header.height; row++) {
				std::vector <Pix> row_data;

				if (existalpha) {
					for (int col = 0; col < dib_header.width; col++) {
						int blue 	= file.get();
						int green 	= file.get();
						int red 	= file.get();
						int alpha 	= file.get();

						row_data.push_back(Pix(red, green, blue, alpha));
					}
				}
				else {
					for (int col = 0; col < dib_header.width; col++) {
						int blue 	= file.get();
						int green 	= file.get();
						int red 	= file.get();
						int alpha 	= 0;

						row_data.push_back(Pix(red, green, blue, alpha));
					}

					/*	表示位圖像素的位元被打包成行。每行的大小透過填滿向上舍入為 4 個 bytes 
						的倍數。必須將填充位元組（不一定是 0）附加到行的末尾，以使行的長度達到
						四個位元組的倍數。 
					*/
					file.seekg(dib_header.width % 4, std::ios::cur);
				}

				// 若影像有翻轉，進行校正
				if (flip) {
					pixels.insert(pixels.begin(), row_data);
				}
				else {
					pixels.push_back(row_data);
				}
			}
			file.close();
		}
	}
}

void BMP::Write(std::string filename, bool save_alpha) {
	std::ofstream file(filename.c_str(), std::ios::out | std::ios::binary);

	if (file.fail()) {
		std::cerr << "[ERROR] Error during read operation.\n";
	}
	else if(!ValidImage()) {
		std::cerr << "[ERROR] It's not a valid bmp file.\n";
	}
	else {
		// 寫入magic number
		bmp_magic magic;
		magic.magic[0] = 'B';
		magic.magic[1] = 'M';
		file.write((char*)(&magic), sizeof(magic));

		// 寫入bmp header
		bmp_header_format bmp_header = {0};
		bmp_header.file_size = save_alpha ? bmp_header.bmp_offset + (pixels[0].size() * 4) * pixels.size() :
							bmp_header.bmp_offset + (pixels[0].size() * 3 + pixels[0].size() % 4) * pixels.size();
		bmp_header.bmp_offset = sizeof(bmp_magic) +
								sizeof(bmp_header_format) +
								sizeof(dib_header_format);
		file.write((char*)(&bmp_header), sizeof(bmp_header));

		// 寫入dib header
		dib_header_format dib_header = {0};
		dib_header.header_size = sizeof(dib_header_format);
		dib_header.width = pixels[0].size();
		dib_header.height = pixels.size();
		dib_header.num_planes = 1;
		dib_header.bits_per_pixel = save_alpha ? 32 : 24;
		dib_header.compression = 0;
		dib_header.bmp_byte_size = 0;
		dib_header.hres = 3780;
		dib_header.vres = 3780;
		dib_header.num_colors = 0;
		dib_header.num_important_colors = 0;
		file.write((char*)(&dib_header), sizeof(dib_header));

		// 寫入pixel matrix
		for (int row = pixels.size() - 1; row >= 0; row--) {
			const std::vector <Pix> & row_data = pixels[row];

			if (save_alpha) {
				for (int col = 0; col < row_data.size(); col++) {
					const Pix& pix = row_data[col];

					file.put((uchar_t)(pix.blue));
					file.put((uchar_t)(pix.green));
					file.put((uchar_t)(pix.red));
					file.put((uchar_t)(pix.alpha));
				}
			}
			else {
				for (int col = 0; col < row_data.size(); col++) {
					const Pix& pix = row_data[col];

					file.put((uchar_t)(pix.blue));
					file.put((uchar_t)(pix.green));
					file.put((uchar_t)(pix.red));
				}

				for (int i = 0; i < row_data.size() % 4; i++) {
					file.put(0);
				}
			}
		}
		file.close();
	}
}

bool BMP::ValidImage() {
	const int height = pixels.size();
	// 確認pixel matrix高度是否為0
	if( height == 0 || pixels[0].size() == 0) {
		std::cerr << "[ERROR] Height is zero.\n";
		return false;
	}

	const int width = pixels[0].size();
	// 確認矩陣寬度是否正確
	for(int row=0; row < height; row++) {
		if( pixels[row].size() != width ) {
			std::cerr << "[ERROR] Width is not correct.\n";
			return false;
		}
		// 檢查每個pixel的每個channel都小於256，大於等於0
		for(int col=0; col < width; col++) {
			Pix pix = pixels[row][col];
			if( pix.red > MAX_VAL || pix.red < MIN_VAL ||
				pix.green > MAX_VAL || pix.green < MIN_VAL ||
				pix.blue > MAX_VAL || pix.blue < MIN_VAL ||
				pix.alpha > MAX_VAL || pix.alpha < MIN_VAL) {
				std::cerr << "[ERROR] Pixel value is greater than 255.\n";
				return false;
			}
		}
	}
	return true;
}

PixMat BMP::ToPixMat() {
	// 檢查像素矩陣是否有問題。若有則回傳空矩陣
	if(ValidImage()) {
		return pixels;
	}
	else {
		return PixMat();
	}
}

// 將矩陣寫入private內的pixel matrix
void BMP::FromPixMat(const PixMat & values) {
	pixels = values;
}