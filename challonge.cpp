#include "challonge.h"
#include <QDebug>
#include <QUrl>
#include <QUrlQuery>
#include <QVariantMap> // for payloads in PUT/POST requests
#include <QByteArray>

Challonge::Challonge()
{
    manager = new QNetworkAccessManager(this);
}

Challonge::~Challonge()
{
    delete manager;
}

/* Public functions below */
void Challonge::setAPIKey(QString key)
{
    api_key = key;
}

void Challonge::getTournaments()
{
    if (api_key.isEmpty())
    {
        qDebug() << "api_key cannot be empty";
        return;
    }
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyReceived(QNetworkReply*)));

    QString request = "https://api.challonge.com/v1/tournaments.json";
    QUrl url(request);
    QUrlQuery params;

    params.addQueryItem("api_key", api_key);
    params.addQueryItem("state", "in_progress");  // only show in_progress tournaments
    url.setQuery(params);
    qDebug() << url.toString();
    manager->get(QNetworkRequest(url)); // will emit finished(QNetworkReply*) when done
}

void Challonge::getParticipants(QString tourney_id)
{
    if (api_key.isEmpty() || tourney_id.isEmpty())
    {
        qDebug() << "api_key/tourney_id cannot be empty";
        return;
    }
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyReceived(QNetworkReply*)));

    QString request = "https://api.challonge.com/v1/tournaments/" + tourney_id + "/participants.json";
    QUrl url(request);
    QUrlQuery params;

    params.addQueryItem("api_key", api_key);
    url.setQuery(params);
    qDebug() << url.toString();
    manager->get(QNetworkRequest(url)); // will emit finished(QNetworkReply*) when done
}

void Challonge::getMatches(QString tourney_id)
{
    if (api_key.isEmpty() || tourney_id.isEmpty())
    {
        qDebug() << "api_key/tourney_id cannot be empty";
        return;
    }
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyReceived(QNetworkReply*)));

    QString request = "https://api.challonge.com/v1/tournaments/" + tourney_id + "/matches.json";
    QUrl url(request);
    QUrlQuery params;

    params.addQueryItem("api_key", api_key);
    url.setQuery(params);
    qDebug() << url.toString();
    manager->get(QNetworkRequest(url)); // will emit finished(QNetworkReply*) when done
}

void Challonge::updateMatches(QString tourney_id, QString match_id, QString score, QString winner)
{
    if (api_key.isEmpty() || tourney_id.isEmpty() || match_id.isEmpty())
    {
        qDebug() << "api_key/tourney_id/match_id cannot be empty";
        return;
    }
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyReceived(QNetworkReply*)));

    QString request = "https://api.challonge.com/v1/tournaments/" + tourney_id + "/matches/" + match_id + ".json";
    QUrl url(request);
    QUrlQuery params;
    QVariantMap feed, feed2;

    params.addQueryItem("api_key", api_key);
    url.setQuery(params);
    qDebug() << url.toString();

    feed.insert("scores_csv", score);
    if (!winner.isEmpty())
        feed.insert("winner_id", winner);
    feed2.insert("match", feed);
    QByteArray payload = QJsonDocument::fromVariant(feed2).toJson();

    QNetworkRequest netRequest(url);
    netRequest.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
    manager->put(netRequest, payload); // PUT request, will emit finished(QNetworkReply*) when done
}
/* End public functions */

/* SIGNAL Function(s) */
void Challonge::replyReceived(QNetworkReply *netReply)
{
    QObject::disconnect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyReceived(QNetworkReply*))); // do not process anything else
    netReply->deleteLater();
    QByteArray* buffer = new QByteArray();
    QJsonDocument jsonDoc;
    QJsonArray jsonArray;

    if (netReply->error() == QNetworkReply::NoError)
    {
        buffer->append(netReply->readAll());
        jsonDoc = QJsonDocument::fromJson(*buffer);
        jsonArray = jsonDoc.array();
        buffer->clear();
    }
    else
    {
        qDebug() << netReply->errorString();
    }
    delete buffer;
    emit returnData(jsonArray);   // whoever is using this class MUST catch this signal using QOBject::connect() in order to get the return data
}
