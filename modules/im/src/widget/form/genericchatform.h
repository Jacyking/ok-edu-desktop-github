/*
    Copyright © 2014-2019 by The qTox Project Contributors

    This file is part of qTox, a Qt-based graphical interface for Tox.

    qTox is libre software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    qTox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with qTox.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GENERICCHATFORM_H
#define GENERICCHATFORM_H

#include "src/chatlog/chatmessage.h"
#include "src/core/toxpk.h"
#include "src/model/ichatlog.h"
#include "src/widget/searchtypes.h"

#include <QMenu>
#include <QWidget>

/**
 * Spacing in px inserted when the author of the last message changes
 * @note Why the hell is this a thing? surely the different font is enough?
 *        - Even a different font is not enough – TODO #1307 ~~zetok
 */

class ChatFormHeader;
class ChatLog;
class ChatTextEdit;
class Contact;
class ContentLayout;
class CroppingLabel;
class FlyoutOverlayWidget;
class GenericNetCamView;
class MaskablePixmapWidget;
class SearchForm;
class Widget;

class QLabel;
class QPushButton;
class QSplitter;
class QToolButton;
class QVBoxLayout;
class QHBoxLayout;
class IMessageDispatcher;
struct Message;

namespace Ui {
class MainWindow;
}

#ifdef SPELL_CHECKING
namespace Sonnet {
class SpellCheckDecorator;
}
#endif

class GenericChatForm : public QWidget
{
    Q_OBJECT
public:
    GenericChatForm(const Contact* contact, IChatLog& chatLog,
                    IMessageDispatcher& messageDispatcher, QWidget* parent = nullptr);
    ~GenericChatForm() override;

    void setName(const QString& newName);
    virtual void show() final
    {
    }
    virtual void show(ContentLayout* contentLayout);
    virtual void reloadTheme();

    void addSystemInfoMessage(const QString& message, ChatMessage::SystemMessageType type,
                              const QDateTime& datetime);
    static QString resolveToxPk(const ToxPk& pk);
    QDateTime getLatestTime() const;
    QDateTime getFirstTime() const;

signals:
    void messageInserted();
    void messageNotFoundShow(SearchDirection direction);

public slots:
    void focusInput();
    void onChatMessageFontChanged(const QFont& font);
    void setColorizedNames(bool enable);

protected slots:
    void onChatContextMenuRequested(QPoint pos);
    virtual void onScreenshotClicked() = 0;
    void onSendTriggered();
    virtual void onAttachClicked() = 0;
    void onEmoteButtonClicked();
    void onEmoteInsertRequested(QString str);
    void onCopyLogClicked();
    void onEncryptButtonClicked();
    void clearChatArea();
    void clearChatArea(bool confirm, bool inform);
    void onSelectAllClicked();
    void showFileMenu();
    void hideFileMenu();
    void onShowMessagesClicked();
    void onSplitterMoved(int pos, int index);
    void quoteSelectedText();
    void copyLink();
    void onLoadHistory();
    void onExportChat();
    void searchFormShow();
    void onSearchTriggered();
    void updateShowDateInfo(const ChatLine::Ptr& prevLine, const ChatLine::Ptr& topLine);

    void searchInBegin(const QString& phrase, const ParameterSearch& parameter);
    void onSearchUp(const QString& phrase, const ParameterSearch& parameter);
    void onSearchDown(const QString& phrase, const ParameterSearch& parameter);
    void handleSearchResult(SearchResult result, SearchDirection direction);
    void renderMessage(ChatLogIdx idx);
    void renderMessages(ChatLogIdx begin, ChatLogIdx end,
                        std::function<void(void)> onCompletion = std::function<void(void)>());

    void loadHistoryLower();

#ifdef OK_PLUGIN
    void onPluginEnabled(const QString &shortName);
    void onPluginDisabled(const QString &shortName);
#endif

private:
    void retranslateUi();
    void addSystemDateMessage(const QDate& date);
    QDateTime getTime(const ChatLine::Ptr& chatLine) const;

protected:
    // ChatMessage::Ptr createMessage(const ToxPk& author, const QString& message,
    //                                const QDateTime& datetime, bool isAction, bool isSent, bool colorizeName = false);
    bool needsToHideName(ChatLogIdx idx) const;
    void showNetcam();
    void hideNetcam();
    virtual GenericNetCamView* createNetcam() = 0;
    virtual void insertChatMessage(ChatMessage::Ptr msg);
    void adjustFileMenuPosition();
    virtual void hideEvent(QHideEvent* event) override;
    virtual void showEvent(QShowEvent*) override;
    virtual bool event(QEvent*) final override;
    virtual void resizeEvent(QResizeEvent* event) final override;
    virtual bool eventFilter(QObject* object, QEvent* event) final override;
    void disableSearchText();
    bool searchInText(const QString& phrase, const ParameterSearch& parameter, SearchDirection direction);
    std::pair<int, int> indexForSearchInLine(const QString& txt, const QString& phrase, const ParameterSearch& parameter, SearchDirection direction);

protected:
    bool audioInputFlag;
    bool audioOutputFlag;
    int curRow;

    QAction* clearAction;
    QAction* quoteAction;
    QAction* copyLinkAction;
    // QAction* searchAction;
    // QAction* loadHistoryAction;
    // QAction* exportChatAction;

    QMenu menu;
    QHBoxLayout *mainFootLayout;
    bool isEncrypt;
    QPushButton* encryptButton;

    QPushButton* emoteButton;
    QPushButton* fileButton;
    QPushButton* screenshotButton;
    QPushButton* sendButton;

    QSplitter* bodySplitter;

    ChatFormHeader* headWidget;

    SearchForm *searchForm;
    QLabel *dateInfo;
    ChatLog* chatWidget;
    ChatTextEdit* msgEdit;
#ifdef SPELL_CHECKING
    Sonnet::SpellCheckDecorator* decorator{nullptr};
#endif
    FlyoutOverlayWidget* fileFlyout;
    GenericNetCamView* netcam;
    Widget* parent;

    IChatLog& chatLog;
    IMessageDispatcher& messageDispatcher;
    SearchPos searchPos;
    std::map<ChatLogIdx, ChatMessage::Ptr> messages;
    bool colorizeNames = false;
};

#endif // GENERICCHATFORM_H
