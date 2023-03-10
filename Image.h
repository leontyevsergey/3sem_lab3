#include<iostream>
#include<iterator>
#include<vector>
using namespace std;

template <typename T>
class Image {
private:
	vector<vector<T>> image;
	size_t width, height;
public:	
		void get_roi(const Image& a_image, size_t& x_min, size_t& y_min, size_t& result_width, size_t& result_height)
		{
			if (width > a_image.width) {
				result_width = width;
				x_min = a_image.width;
			}
			else
			{
				result_width = a_image.width;
				x_min = width;
			}
			if (height > a_image.height) {
				result_height = height;
				y_min = a_image.height;
			}
			else
			{
				result_height = a_image.height;
				y_min = height;
			}
		}

		void copy_outside_roi(const Image& a_image, size_t& x_min, size_t& y_min, size_t& result_width, size_t& result_height, size_t& result_image)
		{
			if (width > a_image.width || width < a_image.width) {
				for (size_t i = x_min; i < result_width; ++i) {
					for (size_t j = 0; j < result_height; ++j) {
						result_image.image[i][j] = image[i][j];
					}
				}
			}
			if (height > a_image.height || height < a_image.height) {
				for (size_t i = 0; i < x_min; ++i) {
					for (size_t j = y_min; j < result_height; ++j) {
						result_image.image[i][j] = image[i][j];
					}
				}
			}
		}

	Image();
	Image(const size_t a_width, const size_t a_height);
	Image(const Image& image_copy);
	~Image();
	T operator()(const size_t a_width, const size_t a_height) const;
	T& operator()(const size_t a_width, const size_t a_height);
	Image operator =(const Image& a_image);
	Image operator *(const Image& a_image) const;
	Image operator +(const Image& a_image) const;
	Image operator *(const T a_b) const;
	Image operator +(const T a_b) const;
	//Image operator !() const;
	bool operator ==(const Image& a_image) const;
	double ratio() const;
	typename vector<vector<T>>::iterator begin() const;
	typename vector<vector<T>>::iterator end() const;
	size_t get_width() const;
	size_t get_height() const;
	void print_im() const;
};


template <typename T>
Image<T>::Image() : image(0), width(0), height(0) {}

template <typename T>
Image<T>::Image(const size_t a_width, const size_t a_height) {
	if (a_width == 0 || a_height == 0) {
		throw std::out_of_range( "The number of rows and columns should be >0" );
	}
	width = a_width;
	height = a_height;
	for (size_t i = 0; i < width; ++i) {
		image.push_back(vector<T>(height));
	}
}

template <typename T>
Image<T>::Image(const Image& image_copy) {
	width = image_copy.width;
	height = image_copy.height;
	image.resize(width);
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			image[i].push_back(image_copy(i, j));
		}
	}
}

template <typename T>
T Image<T>::operator()(const size_t a_width, const size_t a_height) const {
	if (a_width > width || a_height > height)
		throw std::out_of_range( "Incorrect coordinates" );
	return image[a_width][a_height];
}

template <typename T>
T& Image<T>::operator()(const size_t a_width, const size_t a_height) {
	if (a_width > width || a_height > height)
		throw std::out_of_range( "Incorrect coordinates" );
	return image[a_width][a_height];
}

template <typename T>
Image<T> Image<T>::operator =(const Image& a_image) {
	width = a_image.width;
	height = a_image.height;
	if (width != a_image.width || height != a_image.height) {
		if (image) {
			image.clear();
		}
		image.resize(width);
	}
	for (size_t i = 0; i < width; ++i) {
		for (size_t j = 0; j < height; ++j) {
			image[i].push_back(a_image(i, j));
		}
	}
	return a_image;
}

template <typename T>
Image<T> Image<T>::operator*(const Image& a_image) const {
	size_t x_min = 0;
	size_t y_min = 0;
	size_t result_width;
	size_t result_height;
	//get_roi(Image&a_image, x_min, y_min, result_width, result_height);
	//size_t x_min = 0, y_min = 0, result_width, result_height;
	Image<T> im = a_image;
	if (width > a_image.width) {
		result_width = width;
		x_min = a_image.width;
	}
	else
	{
		result_width = a_image.width;
		x_min = width;
	}
	if (height > a_image.height) {
		result_height = height;
		y_min = a_image.height;
	}
	else
	{
		result_height = a_image.height;
		y_min = height;
	}
	Image<T> result_image(result_width, result_height);
	for (size_t i = 0; i < x_min; ++i) {
		for (size_t j = 0; j < y_min; ++j) {
			result_image.image[i][j] = image[i][j] * a_image.image[i][j];
		}
	}
	//copy_outside_roi(Image& a_image, x_min, y_min, result_width, result_height, result_image);
	//return result_image;
	if (width > a_image.width || width < a_image.width) {
		for (size_t i = x_min; i < result_width; ++i) {
			for (size_t j = 0; j < result_height; ++j) {
				result_image.image[i][j] = image[i][j];
			}
		}
	}
	if (height > a_image.height || height < a_image.height) {
		for (size_t i = 0; i < x_min; ++i) {
			for (size_t j = y_min; j < result_height; ++j) {
				result_image.image[i][j] = image[i][j];
			}
		}
	}
	return result_image;
}

template <typename T>
Image<T> Image<T>::operator +(const Image& a_image) const {
	size_t x_min = 0;
	size_t y_min = 0;
	size_t result_width;
	size_t result_height;
	//get_roi(Image& a_image, x_min, y_min, result_width, result_height);
	//size_t x_min = 0, y_min = 0, result_width, result_height;
	Image<T> im = a_image;
	if (width > a_image.width) {
		result_width = width;
		x_min = a_image.width;
	}
	else
	{
		result_width = a_image.width;
		x_min = width;
	}
	if (height > a_image.height) {
		result_height = height;
		y_min = a_image.height;
	}
	else
	{
		result_height = a_image.height;
		y_min = height;
	}
	Image<T> result_image(result_width, result_height);
	for (size_t i = 0; i < x_min; ++i) 
	{
		for (size_t j = 0; j < y_min; ++j) {
			result_image.image[i][j] = image[i][j] + a_image.image[i][j];
		}
	}
	//copy_outside_roi(Image& a_image, x_min, y_min, result_width, result_height, result_image);
	//return result_image;
	if (width > a_image.width || width < a_image.width) {
		for (size_t i = x_min; i < result_width; ++i) {
			for (size_t j = 0; j < result_height; ++j) {
				result_image.image[i][j] = image[i][j];
			}
		}
	}
	if (height > a_image.height || height < a_image.height) {
		for (size_t i = 0; i < x_min; ++i) {
			for (size_t j = y_min; j < result_height; ++j) {
				result_image.image[i][j] = image[i][j];
			}
		}
	}
	return result_image;
}

template <typename T>
Image<T> Image<T>::operator *(const T a_b) const {
	Image<T> result_image(width, height);
	for (auto i = 0; i < width; ++i) {
		for (auto j = 0; j < height; ++j) {
			result_image.image[i][j] = image[i][j] * a_b;
		}
	}
	return result_image;
}

template <typename T>
Image<T> Image<T>::operator +(const T a_b) const {
	Image<T> result_image(width, height);
	for (auto i = 0; i < width; ++i) {
		for (auto j = 0; j < height; ++j) {
			result_image.image[i][j] = image[i][j] + a_b;
		}
	}
	return result_image;
}

/*template <typename T>
Image<T> Image<T>::operator!() const {
	Image<T> result_image(width, height);
	for (auto i = 0; i < width; ++i) {
		for (auto j = 0; j < height; ++j) {
			if (image[i][j] == True)
				result_image.image[i][j] = False;
			else
				result_image.image[i][j] = True;
		}
	}
	return result_image;
}*/

template <typename T>
bool Image<T>::operator ==(const Image& a_image) const {
	if (width == a_image.width && height == a_image.height) {
		for (size_t i = 0; i < width; ++i) {
			for (size_t j = 0; j < height; ++j) {
				if (image[i][j] == a_image.image[i][j])
					continue;
				else
				{
					return false;
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T>
ostream& operator <<(ostream& os, const Image<T>& a_image) {
	size_t k = 0;
	size_t m = 0;
	for (auto i : a_image) {
		for (auto j : i) {
				os << "\t" << a_image(k, m);
				m++;
		}
		os << endl;
		k++;
	}
	return os;
}

template <>
ostream& operator <<(ostream& os, const Image<char>& a_image) {
	for (size_t i = 0; i < a_image.get_width(); ++i) {
		for (size_t j = 0; j < a_image.get_height(); ++j) {
			os << "\t" << (int)a_image(i, j);
		}
		os << endl;
	}
	return os;
}

template <typename T>
double Image<T>::ratio() const {
	double temp = 0, d_width = width, d_height = height;
	for (auto i : image) {
		for (auto j : i) {
			if (j)
				temp++;
		}
	}
	return(temp / (d_width * d_height));
}

template <typename T>
typename vector <vector<T>>::iterator Image<T>::begin() const {
	return image[0].begin();
}

template <typename T>
typename vector<vector<T>>::iterator Image<T>::end() const {
	return image[width - 1].end();
}

template <typename T>
size_t Image<T>::get_width() const {
	return width;
}

template <typename T>
size_t Image<T>::get_height() const {
	return height;
}

template <typename T>
Image<T>::~Image<T>() {}

template <typename T>
void Image<T>::print_im()const
{
	for (auto it : image)
	{
		for (auto iter : it)
			cout << "\t" << iter;
		cout << endl;
	}
}