#include "imagecache.h"

ImageCache::ImageCache()
{

}

void ImageCache::clearCache()
{
    clearCacheNegatives();
    clearCachePositives();
}

void ImageCache::clearCacheNegatives()
{
    m_negativesFull.clear();
    m_negativesThumb.clear();
}

void ImageCache::clearCachePositives()
{
    m_positivesFull.clear();
    m_positivesThumb.clear();
}

int ImageCache::addNegative(const cv::Mat &matFull, const cv::Mat &matThumb)
{
    m_negativesFull.push_back(matFull);
    m_negativesThumb.push_back(matThumb);

    return static_cast<int>(m_positivesFull.size())-1;
}

int ImageCache::addPositive(const cv::Mat &matFull, const cv::Mat &matThumb)
{
    m_positivesFull.push_back(matFull);
    m_positivesThumb.push_back(matThumb);

    return static_cast<int>(m_positivesFull.size())-1;
}

cv::Mat ImageCache::getNegativeFull(int idx)
{
   return m_negativesFull[idx];
}

cv::Mat ImageCache::getNegativeThumb(int idx)
{
    return m_negativesThumb[idx];
}
