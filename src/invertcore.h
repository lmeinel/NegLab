#ifndef INVERTCORE_H
#define INVERTCORE_H

#include <opencv2/opencv.hpp>
#include "inttypes.h"

enum InvertMode
{
    BITWISE_NOT,
    TONE_CURVE
};

class InvertCore
{
public:
    InvertCore();
    ~InvertCore();

    cv::Mat invert(const cv::Mat& input);
    int updateLut();

    InvertMode getMode() const;
    void setMode(const InvertMode &mode);

    int getType() const;
    void setType(int type);

private:
    template <typename T>
    cv::Mat applyLut(const cv::Mat &input);

    InvertMode  m_mode;
    uint16_t*   m_lut;
    int         m_type;
};

#endif // INVERTCORE_H
