#ifndef __tuts__PicoPNG__
#define __tuts__PicoPNG__

#include <vector>

extern int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);

#endif /* defined(__tuts__PicoPNG__) */
