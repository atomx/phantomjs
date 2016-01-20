/*
  This file is part of the PhantomJS project from Ofi Labs.

  Copyright (C) 2011 Ariya Hidayat <ariya.hidayat@gmail.com>
  Copyright (C) 2015 Dmitry Parshin, Smartling Inc. <dparshin@smartling.com>, <parshin.da@gmail.com>

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef NETWORKREPLYPROXY_H
#define NETWORKREPLYPROXY_H

#include <QNetworkReply>


/*
  Proxy class for QNetworkReply. Collects response body, which can
  be retreived using 'body' method.
 */
class NetworkReplyProxy : public QNetworkReply
{
    Q_OBJECT
public:

    /*
      reply - reply to be proxied(nested reply)
      m_captureContentPatterns - patterns for which we should capture the response body
     */
    NetworkReplyProxy(QObject* parent, QNetworkReply* reply,
                      QStringList m_captureContentPatterns);


    /*
      Returns collected body
     */
    QString body();

    /*
      Returns the body size. Even if body isn't being captured.
     */
    int bodySize();


    /*
      Returns nested reply
     */
    QNetworkReply* nestedReply() const
    {
        //TODO: in cpp
        return m_reply;
    };


    // QNetworkReply proxied methods
    void abort();
    void close();
    bool isSequential() const;

    // not possible...
    void setReadBufferSize(qint64 size);

    // QIODevice proxy...
    virtual qint64 bytesAvailable() const;
    virtual qint64 bytesToWrite() const;
    virtual qint64 readData(char* data, qint64 maxlen);

    bool shouldCaptureResponse(const QString& contentType);

public Q_SLOTS:
    void ignoreSslErrors();
    void applyMetaData();

    void errorInternal(QNetworkReply::NetworkError _error);
    void readInternal();

private:
    QNetworkReply* m_reply;
    QByteArray m_data;
    QByteArray m_buffer;
    bool m_shouldCaptureResponseBody;
    QList<QRegExp> m_compiledCaptureContentPatterns;
    int m_dataSize;
};

#endif // NETWORKREPLYPROXY_H
