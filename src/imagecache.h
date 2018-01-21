#ifndef IMAGECACHE_H
#define IMAGECACHE_H

#include <opencv2/opencv.hpp>

class ImageCache
{
public:
    ImageCache();
    void clearCache();
    void clearCacheNegatives();
    void clearCachePositives();
    int addNegative(const cv::Mat &matFull, const cv::Mat &matThumb);
    int addPositive(const cv::Mat &matFull, const cv::Mat &matThumb);
    cv::Mat getNegativeFull(int idx);
    cv::Mat getPositiveFull(int idx);
    cv::Mat getNegativeThumb(int idx);
    cv::Mat getPositiveThumb(int idx);

private:
    std::vector<cv::Mat> m_negativesFull;
    std::vector<cv::Mat> m_positivesFull;
    std::vector<cv::Mat> m_negativesThumb;
    std::vector<cv::Mat> m_positivesThumb;
};

#endif // IMAGECACHE_H
