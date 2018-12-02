#include "invertcore.h"

InvertCore::InvertCore()
 :  m_type(CV_8UC1),
    m_lut(nullptr)

{

}

InvertCore::~InvertCore()
{

}

cv::Mat InvertCore::invert(const cv::Mat& input)
{
    if(input.empty())
        return cv::Mat();

    cv::Mat output;

    if(m_mode == BITWISE_NOT)
    {
        cv::bitwise_not(input, output);
    }
    else if(m_mode == TONE_CURVE)
    {
        if(m_type == CV_8UC1)
        {
            output = applyLut<uint8_t>(input);
        }
        else if(m_type == CV_16UC1)
        {
            output = applyLut<uint16_t>(input);
        }
    }

    return output;
}

int InvertCore::updateLut()
{
    assert(m_type == CV_8UC1 || m_type == CV_16UC1);

    if (m_lut)
        delete[] m_lut;

    if (m_type == CV_8UC1)
    {
        m_lut = new uint16_t[256];

        for(uint16_t i = 0; i < 256; i++)
        {
            m_lut[i] = static_cast<uint16_t>(applyToneCurve(i));
        }

        return m_type;
    }
    else if (m_type == CV_16UC1)
    {
        m_lut = new uint16_t[65536];

        for(int i = 0; i < 65536; i++)
        {
            m_lut[i] = static_cast<uint16_t>(applyToneCurve(i));
        }

        return m_type;
    }

    return -1;
}

InvertMode InvertCore::getMode() const
{
    return m_mode;
}

void InvertCore::setMode(const InvertMode &mode)
{
    m_mode = mode;
}

int InvertCore::getType() const
{
    return m_type;
}

void InvertCore::setType(int type)
{
    m_type = type;
}

int InvertCore::setNegHighDensity(int value)
{
    m_neghd = value;
    return m_neghd;
}

int InvertCore::setNegLowDensity(int value)
{
    m_negld = value;
    return m_negld;
}

int InvertCore::setPosWhite(int value)
{
    m_posw = value;
    return m_posw;
}

int InvertCore::setPosBlack(int value)
{
    m_posb = value;
    return m_posb;
}

int InvertCore::setNegHighDensity(const cv::Mat &sample, cv::Rect roi)
{
    cv::Scalar value = cv::mean(sample(roi));
    m_neghd = static_cast<int>(value[0]);

    return m_neghd;
}

int InvertCore::setNegLowDensity(const cv::Mat &sample, cv::Rect roi)
{
    cv::Scalar value = cv::mean(sample(roi));
    m_negld = static_cast<int>(value[0]);

    return m_negld;
}

int InvertCore::applyToneCurve(int input)
{
    assert(m_type == CV_8UC1 || m_type == CV_16UC1);

    int output = static_cast<int>((static_cast<double>(m_posb - m_posw)/static_cast<double>(m_negld - m_neghd)) * static_cast<double>(input - m_neghd) + (m_posw));

    if(m_type == CV_8UC1)
    {
        if(output < 0)
            output = 0;

        if(output > 255)
            output = 255;
    }
    else
    {
        if(output < 0)
            output = 0;

        if(output > 65535)
            output = 65535;
    }

    return output;
}

template <typename T>
cv::Mat InvertCore::applyLut(const cv::Mat &input)
{
    if(!m_lut)
        return cv::Mat();

    if(input.type() != m_type)
        return cv::Mat();

    if(input.empty())
        return cv::Mat();

    // create properly sized output
    cv::Mat output(input.rows, input.cols, input.type());

    // fast element access
    int rows, cols;
    if (input.isContinuous())
    {
        rows = 1;
        cols = input.rows * input.cols;
    }
    else
    {
        rows = input.rows;
        cols = input.cols;
    }

    for (int r = 0; r < rows; r++)
    {
        //start pointer for current line
        const T*  p_input  = input.ptr<const T>(r);
        T*  p_output  = output.ptr<T>(r);

        // iterate over line
        for(int c = 0; c < cols; c++)
        {
            p_output[c] = static_cast<T>(m_lut[p_input[c]]);
        }
    }

    return output;
}
