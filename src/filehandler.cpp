#define NEGLAB_FH_DEBUG

#include "filehandler.h"

#include <QDir>

#ifdef NEGLAB_FH_DEBUG
#include <QDebug>
#endif

FileHandler::FileHandler()
    : m_fileList(nullptr)
{

}

FileHandler::~FileHandler()
{

}

int FileHandler::analyzeDirectory()
{
    QDir dir(m_inputPath);

    if (!dir.exists())
    {
        qWarning("Cannot find the example directory");
        return -1;
    }

    QStringList nameFilterList(m_nameFilter);
    m_fileList = dir.entryList(nameFilterList);

#ifdef NEGLAB_FH_DEBUG
    QString debug = m_fileList.join(", ");
    qDebug() << debug;
#endif

    return 0;
}

QStringList FileHandler::getFileList() const
{
    return m_fileList;
}

QString FileHandler::getInputPath() const
{
    return m_inputPath;
}

QString FileHandler::getOutputPath() const
{
    return m_outputPath;
}

void FileHandler::setInputPath(const QString &inputPath)
{
    m_inputPath = inputPath;
}

void FileHandler::setOutputPath()
{
    QDir inputDir(m_inputPath);
    inputDir.cdUp();

    m_outputPath = QDir::cleanPath(inputDir.absolutePath() + QDir::separator() + "positive");
}

void FileHandler::setOutputPath(const QString &outputPath)
{
    m_outputPath = outputPath;
}

QString FileHandler::getNameFilter() const
{
    return m_nameFilter;
}

void FileHandler::setNameFilter(const QString &nameFilter)
{
    m_nameFilter = nameFilter;
}

QString FileHandler::getOutputPrefix() const
{
    return m_outputPrefix;
}

void FileHandler::setOutputPrefix(const QString &outputPrefix)
{
    m_outputPrefix = outputPrefix;
}

QString FileHandler::getOutputType() const
{
    return m_outputType;
}

void FileHandler::setOutputType(const QString &outputType)
{
    m_outputType = outputType;
}
