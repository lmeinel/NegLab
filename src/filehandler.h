#ifndef FILEHANDLER_H
#define FILEHANDLER_H

//#include <string>
//#include <vector>

#include <QString>
#include <QStringList>

class FileHandler
{
public:
    FileHandler();
    ~FileHandler();

    int analyzeDirectory();

    // getter
    QString getInputPath() const;
    QString getNameFilter() const;
    QStringList getFileList() const;

    QString getOutputPath() const;
    QString getOutputPrefix() const;
    QString getOutputType() const;

    // setter
    void setInputPath(const QString &inputPath);
    void setNameFilter(const QString &nameFilter);

    void setOutputPath();
    void setOutputPath(const QString &outputPath);
    void setOutputPrefix(const QString &outputPrefix);
    void setOutputType(const QString &outputType);

private:
    // input files
    QString     m_inputPath;
    QString     m_nameFilter;
    QStringList m_fileList;

    // output files
    QString     m_outputPath;
    QString     m_outputPrefix;
    QString     m_outputType;
};

#endif // FILEHANDLER_H
