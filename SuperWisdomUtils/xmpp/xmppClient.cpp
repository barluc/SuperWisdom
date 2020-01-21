#include "xmppClient.h"




xmppClient::xmppClient()
{
}

xmppClient::~xmppClient()
{
}

void xmppClient::start()
{
	//XMPP��¼
	serverJid.setUsername(commonslib::Utils::number2String(m_userPtr->userId));
	serverJid.setServer(m_configPtr->XMPPDomain);
	serverJid.setResource(XMPPResourse);
	xmppClient_ptr = shared_ptr<gloox::Client>(new Client(serverJid, m_userPtr->password, m_configPtr->XMPPPort), [](gloox::Client* t)->void {if (t != nullptr) { t->disconnect(); delete t; }});
	xmppClient_ptr->setServer(m_configPtr->XMPPHost);
	//            xmppClient_ptr->disco()->addFeature(XMLNS_CHAT_STATES);
	xmppClient_ptr->disco()->addFeature(XMLNS_COMPRESSION);
	xmppClient_ptr->disco()->addFeature(XMLNS_OFFLINE);
	xmppClient_ptr->setStreamManagement(true, true);
	xmppClient_ptr->registerConnectionListener(this);
	xmppClient_ptr->registerMessageHandler(this);
	xmppClient_ptr->registerPresenceHandler(this);

	//���������� ������ܲ�����Ϣ��ִ Ҳ����<received xmlns="urn:xmpp:receipts" id="f2dfe3a9089e493e94f430ad481e2d28" status="1"></received>
	xmppClient_ptr->registerStanzaExtension(new gloox::Receipt(Receipt::Received));
	xmppClient_ptr->logInstance().registerLogHandler(LogLevelDebug, LogAreaAll, this);
	xmppClient_ptr->registerIqHandler(this, gloox::StanzaExtensionType::ExtReceipt);

	xmppClient_ptr->connect(true);
}

void xmppClient::setUser(shared_ptr<User> userPtr)
{
	userPtr->copy(m_userPtr.get());
}

void xmppClient::logoutXmpp()
{
	//������ȡ��ע����� ��Ȼ����mucroom���� ��Ҫ�� removeLogHandler
	if (xmppClient_ptr) {
		xmppClient_ptr->removeConnectionListener(this);
		xmppClient_ptr->removeMessageHandler(this);
		xmppClient_ptr->removePresenceHandler(this);
		xmppClient_ptr->removeStanzaExtension(ExtReceipt);
		xmppClient_ptr->logInstance().removeLogHandler(this);
		xmppClient_ptr->removeIqHandler(this, gloox::StanzaExtensionType::ExtPing);
	}



}

void xmppClient::disconnect()
{
	if (xmppClient_ptr)
	{
		xmppClient_ptr->disconnect();
	}
}

void xmppClient::setImEventCall(shared_ptr<ImEventcall> imCallback)
{
	this->m_imCallback = shared_ptr<ImEventcall>(imCallback);
}

void xmppClient::onConnect()
{
	std::cout << "xmpp������";
	if (m_imCallback) {
		m_imCallback->xmppConnect();
	}
	
}

void xmppClient::onDisconnect(gloox::ConnectionError connError)
{
	if (connError == gloox::ConnStreamError)
	{
		StreamError error = xmppClient_ptr->streamError();
		if (error == gloox::StreamErrorConflict) {//��������
			if (m_imCallback)
			{
				m_imCallback->logout(ImEventcall::LogoutReason::Conflict);
			}
			return;
		}
	}
	if (m_imCallback)
	{
		m_imCallback->xmppDisconnect();
	}
	//��������
	if (m_bLogin && !m_bLogout && xmppClient_ptr) 
	{
		auto task = pplx::task<void>([=]
		{
				std::this_thread::sleep_for(std::chrono::seconds(1));
				std::cout << ("��������xmpp������");
				xmppClient_ptr->connect(true);
		});
	}

}

bool xmppClient::onTLSConnect(const gloox::CertInfo& info)
{
	return true;
}

void xmppClient::onResourceBind(const std::string& resource)
{
	printf("xmpp����Դ");
}

void xmppClient::onResourceBindError(const gloox::Error* pError)
{
	string strError = pError->text();
	if (m_imCallback) {
		m_imCallback->xmppError(strError);
	}
	std::cout << ("xmpp����Դ����:" + strError);
}

void xmppClient::onSessionCreateError(const gloox::Error* pError)
{
	string strError = pError->text();
	if (m_imCallback) {
		m_imCallback->xmppError(strError);
	}
	std::cout << ("xmpp�����Ự����:" + strError);
}

void xmppClient::handleMessage(const gloox::Message& msg, gloox::MessageSession* session)
{
	printf("type: %d, subject: %s, message: %s, thread id: %s\n", msg.subtype(),
		msg.subject().c_str(), msg.body().c_str(), msg.thread().c_str());
	if (session) {
		xmppClient_ptr->disposeMessageSession(session);
	}
}

bool xmppClient::handleIq(const gloox::IQ& iq)
{
	std::cout << ("���յ�iq��Ϣ��" + iq.xmlLang());
	return true;
}

void xmppClient::handleIqID(const gloox::IQ& iq, int context)
{
	std::cout << ("���յ�iq-id��Ϣ����" + to_string(context) + "��" + iq.xmlLang());
	string xml = iq.xmlLang();
}

void xmppClient::handleTag(gloox::Tag* tag)
{
}

void xmppClient::handleMUCParticipantPresence(gloox::MUCRoom* room, const gloox::MUCRoomParticipant participant, const gloox::Presence& presence)
{
}

void xmppClient::handleMUCMessage(gloox::MUCRoom* room, const gloox::Message& msg, bool priv)
{
}

bool xmppClient::handleMUCRoomCreation(gloox::MUCRoom* room)
{
	return false;
}

void xmppClient::handleMUCSubject(gloox::MUCRoom* room, const std::string& nick, const std::string& subject)
{
}

void xmppClient::handleMUCInviteDecline(gloox::MUCRoom* room, const gloox::JID& invitee, const std::string& reason)
{
}

void xmppClient::handleMUCError(gloox::MUCRoom* room, gloox::StanzaError error)
{
}

void xmppClient::handleMUCInfo(gloox::MUCRoom* room, int features, const std::string& name, const gloox::DataForm* infoForm)
{
}

void xmppClient::handleMUCItems(gloox::MUCRoom* room, const gloox::Disco::ItemList& items)
{
}

void xmppClient::handleMUCConfigForm(gloox::MUCRoom* room, const gloox::DataForm& form)
{
}

void xmppClient::handleLog(gloox::LogLevel level, gloox::LogArea area, const std::string& message)
{
}

void xmppClient::handleEvent(const gloox::Event& event)
{
}

void xmppClient::handlePresence(const gloox::Presence& presence)
{
	std::cout << ("xmpp presence֪ͨ:" + presence.tag()->xml());
}
