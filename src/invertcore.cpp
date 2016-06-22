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
    if (m_lut)
        delete[] m_lut;

    if (m_type == CV_8UC1)
    {
        m_lut = new uint16_t[256];

        for(uint16_t i = 0; i < 256; i++)
        {
            m_lut[i] = 255 - i;
        }

        return m_type;
    }
    else if (m_type == CV_16UC1)
    {
        m_lut = new uint16_t[65536];

        for(uint32_t i = 0; i < 65536; i++)
        {
            m_lut[i] = static_cast<uint16_t>(65535 - i);
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
