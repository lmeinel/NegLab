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

    int applyToneCurve(int input);

    InvertMode getMode() const;
    void setMode(const InvertMode &mode);

    int getType() const;
    void setType(int type);

    int setNegHighDensity(int value);
    int setNegLowDensity(int value);
    int setPosWhite(int value);
    int setPosBlack(int value);

    int setNegHighDensity(const cv::Mat& sample, cv::Rect roi = cv::Rect());
    int setNegLowDensity(const cv::Mat& sample, cv::Rect roi = cv::Rect());

private:
    template <typename T>
    cv::Mat applyLut(const cv::Mat &input);


    InvertMode  m_mode;
    uint16_t*   m_lut;
    int         m_type;

    int         m_neghd;
    int         m_negld;
    int         m_posw;
    int         m_posb;
};

#endif // INVERTCORE_H
