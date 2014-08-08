/*
 * File:   main.cpp
 * Author: DrSobik
 *
 * Created on July 15, 2014, 6:25 PM
 */

#include <QApplication>
#include <QObject>
#include <QThread>
#include <QString>
#include <qmath.h>

#include <string>

#include "Object"
#include "Clonable"
#include "Runnable"
#include "Assignable"
#include "Functor"
#include "Comparable"
#include "SavableRestorable"
#include "WritableReadable"
#include "Exceptions"
#include "Operationable"
#include "SmartPointer"
#include "MathExt"
#include "RandExt"

#include "../Sender/Sender.h"

#include <QTextStream>
#include <QVector>

#include <string>
#include <QtCore/qobjectdefs.h>
#include <QtCore/qobject.h>

using namespace std;

using namespace Common;
using namespace Common::Interfaces;
using namespace Common::Exceptions;
using namespace Common::SmartPointers;
using namespace Common::Rand;

class OB1 : public QObject {
};

class OB2 : public QObject {
};

class D : public OB1 {
	Q_OBJECT

public:

signals:

	void someSig();

public slots:

	void someSlot() {
	}

public:

	D() {
		QObject::connect(this, SIGNAL(someSig()), this, SLOT(someSlot()));
	}

};

class Cloner : public Object<>, Clonable {
public:
	int x;

	Cloner() : BasicObject(), Clonable() {
		x = -1;
	}

	Cloner(const Cloner& other) : BasicObject(), Object(other), Clonable() {
		x = other.x;
	}

	virtual ~Cloner() {
		QTextStream out(stdout);
		//out << "~Cloner()" << endl;
	}

	virtual Cloner* clone() {
		return new Cloner(*this);
	}

};

class Assigner : public Object<QObject>, AssignableFrom<const Assigner&> {
public:
	int x;

	Assigner() : BasicObject(), Object(), AssignableFrom() {

	}

	Assigner(const Assigner& other) : BasicObject(), Object(other), AssignableFrom() {

	}

	Assigner& operator=(const Assigner& other) {

		x = other.x;

		return *this;

	}

};

class AssignerClonner : public Object<QObject>, AssignableFrom<const AssignerClonner&>, ClonableTo<AssignerClonner> {
public:
	int x;

	AssignerClonner() : BasicObject(), Object(), AssignableFrom(), ClonableTo() {

	}

	AssignerClonner(const AssignerClonner& other) : BasicObject(), Object(other), AssignableFrom(), ClonableTo() {

		x = other.x;

	}

	AssignerClonner& operator=(const AssignerClonner& other) {

		AssignerClonner& o = (AssignerClonner&) other;

		x = o.x;

		return *this;

	}

	virtual AssignerClonner* clone() {
		return new AssignerClonner(*this);
	}

};

class Dfunctor : public Functor<double, double, double> {
public:

	virtual double operator()(const double& x1, const double& x2) {
		return 150.0 + x1 + x2;
	}

};

class Comparator : public ComparableTo<Comparator> {
public:

	int x;

	Comparator(const int& x) {
		this->x = x;
	}

	virtual bool operator==(const Comparator& x) {
		return this->x == x.x;
	}

	virtual bool operator<(const Comparator& x) {
		return this->x < x.x;
	}

};

class ComparatorEQnEQ : public ComparableEqTo<ComparatorEQnEQ> {
public:
	int x;

	virtual bool operator==(const ComparatorEQnEQ& other) {
		return x == other.x;
	}

};

class SR : public SavableRestorable {
public:
	int x;
	int savedX;

	virtual ~SR() {

	}

	virtual void save() {
		savedX = x;
	}

	virtual void restore() {
		x = savedX;
	}

};

class SToRFrom : public SavableToRestorableFrom<int, int> {
private:
	int x;

public:

	SToRFrom() : SavableToRestorableFrom() {

	}

	void setX(int x) {
		this->x = x;
	}

	int getX() const {
		return x;
	}

	virtual void saveTo(int& other) {
		other = x;
	}

	virtual void restoreFrom(const int& other) {
		x = other;
	}

};

class WR : public WritableToReadableFrom<QTextStream, QTextStream> {
private:
	int x;

public:

	void setX(int x) {
		this->x = x;
	}

	int getX() const {
		return x;
	}

	virtual QTextStream& operator>>(QTextStream& out) const {

		out << "Written : " << getX() << endl;

		return out;
	}

	virtual QTextStream& operator<<(QTextStream& in) {

		QTextStream out(stdout);

		out << "Enter a number : " << endl;

		int readX = -1;

		in >> readX;

		setX(readX);

		return in;
	}

};

class NonAssigner : public AssignableFrom<const double&>, NonAssignableFrom<unsigned int>, NonAssignableFrom<QString> {
private:
	double x;

public:

	virtual AssignableFrom& operator=(const double& otherD) {
		x = otherD;

		return *this;
	}

};

class NonAssigner1 : public NonAssignableFrom<Object<>>
{
	private:
	double x;

	public:

	//virtual NonAssignableFrom<Object<>>& operator=(const Object<>& other){
	//x = other.x;

	//	return *this;
	//}

};

class Deleter {
public:

	const char* x;

	Deleter() : x(NULL) {

	}

	Deleter(const char* msg) : x(NULL) {
		x = new char[strlen(msg) + 1];

		strcpy((char*) x, msg);
	}

	virtual ~Deleter() {
		if (x != NULL) {
			delete[] x;
		}
	}

};

class Additor : public Addible<Additor>, public Subtractable<Additor>, Multipliable<Additor>, Divisible<Additor> {
public:
	int x;

	Additor() : Addible(), Subtractable(), Multipliable(), Divisible() {

	}

	Additor(const Additor& other) : Addible(), Subtractable(), Multipliable(), Divisible() {
		x = other.x;
	}

	Additor(const int& other) {
		x = other;
	}

	virtual Additor& operator+=(const Additor& other) {
		x += other.x;

		return *this;
	}

	virtual Additor& operator-=(const Additor& other) {
		x -= other.x;
		return *this;
	}

	virtual Additor& operator*=(const Additor& other) {
		x *= other.x;
		return *this;
	}

	virtual Additor& operator/=(const Additor& other) {
		x /= other.x;
		return *this;
	}

};

class Inv : public Inversible<Inv&> {
public:
	double x;

	virtual Inv& inv() {

		if (x == 0.0) {
			x = 10E300;

			MessageWritableTo<QTextStream> errMsg;

			errMsg.setMsgData("Inv::void inv() : division by 0!");

			throw ErrMsgException<MessageWritableTo<QTextStream> >(errMsg);
		};

		x = 1.0 / x;

		return *this;
	}

};

class ThreadRunnable : public Object<QObject>, RunnableIn<QThread> {

	Q_OBJECT
public:

	ThreadRunnable() {

		connect(&env, SIGNAL(started()), this, SLOT(runActions()));

		this->moveToThread(&env);

	}

	virtual ~ThreadRunnable() {

		env.quit();
		env.wait();

	}

signals:

	void sigFinished();

public slots:

	void runActions() {

		QTextStream out(stdout);

		out << "Running object : " << objectName() << endl;

		double x = 0.00000000000000000000000000000000000000000000001;
		for (int i = 0; i < 100000000; i++) {
			x += sqrt(x) + pow(x, 0.000001);
		}

		out << x << endl;

		out << "Finished running : " << objectName() << endl;


		emit ThreadRunnable::sigFinished();

	}

	void run() {

		env.start();

	}

};

class SomeClonable1 : public ClonableTo<SomeClonable1>, public Clonable {
public:

	QString name;

	const QString type;

	SomeClonable1() : ClonableTo<SomeClonable1>(), Clonable(), type(QString("SomeClonable1")) {

	}

	SomeClonable1(const SomeClonable1&) : ClonableTo<SomeClonable1>(), Clonable(), type(QString("SomeClonable1")) {

	}

	virtual ~SomeClonable1() {
		QTextStream out(stdout);
		out << name + "::~SomeClonable1()" << endl;
	}

	SomeClonable1* clone() {

		QTextStream out(stdout);
		out << name + "::SomeClonable1::clone()" << endl;

		return new SomeClonable1(*this);

	}

};

class SomeClonable2 : public ClonableTo<SomeClonable2> {
public:

	QString name;
	int x;
	QString something1;
	const QString type;

	SomeClonable2() : ClonableTo(), type(QString("SomeClonable2")) {

	}

	SomeClonable2(const SomeClonable2&) : ClonableTo(), type(QString("SomeClonable2")) {

	}

	virtual ~SomeClonable2() {
		QTextStream out(stdout);
		out << name + "::~SomeClonable2()" << endl;
	}

	SomeClonable2* clone() {

		QTextStream out(stdout);
		out << "SomeClonable2::clone()" << endl;

		return new SomeClonable2(*this);

	}

};

class Subscriptor : public Subscriptable<QVector<int>, int> {
public:

	QVector<QVector<int>> data;

	Subscriptor() : Subscriptable<QVector<int>, int>() {

	}

	Subscriptor(const Subscriptor&) : Subscriptable<QVector<int>, int>() {

	}

	virtual ~Subscriptor() {

	}

	virtual QVector<int>& operator[](const int& idx) {
		return data[idx];
	}

	virtual const QVector<int>& operator[](const int& idx) const {
		return data[idx];
	}


};

class Evt1 {
};

class Evt2 {
};

class Evt3 : public Evt1 {
};

class EvtReceiver : public Object<QObject>, ReceiverOf<Evt1>, ReceiverOf<Evt2>, ReceiverOf<Evt3> {

	Q_OBJECT

public:

	EvtReceiver() {
	}

	EvtReceiver(const EvtReceiver&other) : BasicObject(other), Object(other), ReceiverOf<Evt1>(), ReceiverOf<Evt2>(), ReceiverOf<Evt3>() {
	}

	virtual ~EvtReceiver() {
	}

public slots:

	virtual void receive(Evt1*) {

		QTextStream out(stdout);

		out << "EvtReceiver::receive : Evt1" << endl;

	}

	virtual void receive(Evt2*) {

		QTextStream out(stdout);

		out << "EvtReceiver::receive : Evt2" << endl;

	}

	virtual void receive(Evt3*) {

		QTextStream out(stdout);

		out << "EvtReceiver::receive : Evt3" << endl;

	}

};


// The Qt Sender API which uses signals and slots

class QtSenderAPI : public QObject, SenderAPI<Evt1>, SenderAPI<Evt2>, SenderAPI<Evt3> {

	Q_OBJECT

public:

	QtSenderAPI() {

	}

	QtSenderAPI(const QtSenderAPI& other) : QObject((QObject*) & other), SenderAPI<Evt1>(), SenderAPI<Evt2>(), SenderAPI<Evt3>() {

	}

	// Evt1

	virtual void addReceiver(const ReceiverOf<Evt1>& receiver) {
		QObject::connect(this, SIGNAL(sigEvt(Evt1*)), (EvtReceiver*) & receiver, SLOT(receive(Evt1*)));
	}

	virtual void removeReceiver(const ReceiverOf<Evt1>& receiver) {
		QObject::disconnect(this, SIGNAL(sigEvt(Evt1*)), (EvtReceiver*) & receiver, SLOT(receive(Evt1*)));
	}

	virtual void removeAllReceiversOf(const Evt1&) {
		QObject::disconnect(SIGNAL(sigEvt(Evt1*)));
	}
	
	virtual void send(Evt1* evt) {
		emit sigEvt(evt);
	}

	// Evt2

	virtual void addReceiver(const ReceiverOf<Evt2>& receiver) {
		QObject::connect(this, SIGNAL(sigEvt(Evt2*)), (EvtReceiver*) & receiver, SLOT(receive(Evt2*)));
	}

	virtual void removeReceiver(const ReceiverOf<Evt2>& receiver) {
		QObject::disconnect(this, SIGNAL(sigEvt(Evt2*)), (EvtReceiver*) & receiver, SLOT(receive(Evt2*)));
	}
	
	virtual void removeAllReceiversOf(const Evt2&){
		QObject::disconnect(SIGNAL(sigEvt(Evt2*)));
	}

	virtual void send(Evt2* evt) {
		emit sigEvt(evt);
	}

	// Evt3

	virtual void addReceiver(const ReceiverOf<Evt3>& receiver) {
		QObject::connect(this, SIGNAL(sigEvt(Evt3*)), (EvtReceiver*) & receiver, SLOT(receive(Evt3*)));
	}

	virtual void removeReceiver(const ReceiverOf<Evt3>& receiver) {
		QObject::disconnect(this, SIGNAL(sigEvt(Evt3*)), (EvtReceiver*) & receiver, SLOT(receive(Evt3*)));
	}

	virtual void removeAllReceiversOf(const Evt3&){
		QObject::disconnect(SIGNAL(sigEvt(Evt3*)));
	}
	
	virtual void send(Evt3* evt) {
		emit sigEvt(evt);
	}


signals:
	void sigEvt(Evt1*);
	void sigEvt(Evt2*);
	void sigEvt(Evt3*);

};

template<class T> class OtherSenderAPI : public DefaultSenderAPI<T> {

public : 

	virtual void send(T* evt) {
		qDebug("Some other sender API...");
		DefaultSenderAPI<T>::send(evt);
	}
	
};

class EvtSender : public Object<QObject>, public SenderOf<Evt1, QtSenderAPI>, public SenderOf<Evt2>, public SenderOf<Evt3, OtherSenderAPI<Evt3>> {
public:

	EvtSender() {

	}

	EvtSender(const EvtSender & other) : BasicObject(other), Object(other), SenderOf<Evt1, QtSenderAPI>(other), SenderOf<Evt2>(other), SenderOf<Evt3, OtherSenderAPI<Evt3>>(other) {

	}

	virtual ~EvtSender() {

	}


	// Unhide the inherited methods

	// Evt1
	using SenderOf<Evt1, QtSenderAPI>::addReceiver;
	using SenderOf<Evt1, QtSenderAPI>::removeReceiver;
	using SenderOf<Evt1, QtSenderAPI>::removeAllReceiversOf;
	using SenderOf<Evt1, QtSenderAPI>::send;

	// Evt2
	using SenderOf<Evt2>::addReceiver;
	using SenderOf<Evt2>::removeReceiver;
	using SenderOf<Evt2>::removeAllReceiversOf;
	using SenderOf<Evt2>::send;

	// Evt3
	using SenderOf<Evt3, OtherSenderAPI<Evt3>>::addReceiver;
	using SenderOf<Evt3, OtherSenderAPI<Evt3>>::removeReceiver;
	using SenderOf<Evt3, OtherSenderAPI<Evt3>>::removeAllReceiversOf;
	using SenderOf<Evt3, OtherSenderAPI<Evt3>>::send;

};


#include "main.moc"

template<class T> void foo(T r) {
	++r;
}

void senderReceiverTest() {
	EvtSender sender;
	EvtReceiver receiver;

	sender.addReceiver((ReceiverOf<Evt1>&)receiver);
	sender.addReceiver((ReceiverOf<Evt2>&)receiver);
	sender.addReceiver((ReceiverOf<Evt3>&)receiver);
	
	//sender.removeReceiver((ReceiverOf<Evt1>&)receiver);
	sender.removeAllReceiversOf(Evt3());

	sender.send((Evt1*) NULL);
	sender.send((Evt2*) NULL);
	sender.send((Evt3*) NULL);

}

int main(int argc, char *argv[]) {
	// initialize resources, if needed
	// Q_INIT_RESOURCE(resfile);

	QApplication app(argc, argv);

	QTextStream out(stdout);

	Cloner x1;
	x1.x = 11;

	out << "Created Cloner x1.x= " << x1.x << endl;

	out << "Clonning ... " << endl;
	Cloner* x2 = x1.clone();

	out << "Created Cloner x2.x= " << x2->x << endl;

	delete x2;

	Assigner as1;
	as1.x = 50;

	out << "Created Assigner as1.x= " << as1.x << endl;

	out << "Copying..." << endl;

	Assigner as2;
	as2 = as1;

	out << "Created Assigner as2.x= " << as2.x << endl;

	AssignerClonner asc1;
	asc1.x = 100;

	out << "Created AssignerClonner asc1.x= " << asc1.x << endl;

	out << "Copying..." << endl;

	AssignerClonner asc2;
	asc2 = *asc1.clone();

	out << "Created AssignerClonner asc2.x= " << asc2.x << endl;

	Dfunctor functor;

	out << "Returning value of the functor : " << functor(1, 2) << endl;

	Comparator c(200);

	c.x = 200;

	if (c < 250) {
		out << "Comparator : x < 250" << endl;
	}

	if (c == 200) {
		out << "Comparator : x == 200" << endl;
	}

	if (c <= 200) {
		out << "Comparator : x <= 200" << endl;
	}

	if (c >= 200) {
		out << "Comparator : x >= 200" << endl;
	}

	if (c >= 199) {
		out << "Comparator : x >= 199" << endl;
	}

	if (c > 199) {
		out << "Comparator : x > 199" << endl;
	}

	if (c != 150) {
		out << "Comparator : x != 150" << endl;
	}

	Comparator c2(500);

	c2.x = 500;
	if (c < c2) {
		out << "Comparator : c < c2" << endl;
	}


	ComparatorEQnEQ cen1;
	cen1.x = 10;

	ComparatorEQnEQ cen2;
	cen2.x = 20;

	if (cen1 != cen2) {
		out << "cen1 != cen2" << endl;
	}

	SR sr;
	sr.x = 111;
	sr.save();

	sr.x = 0;

	sr.restore();

	out << "Restored x : " << sr.x << endl;

	SToRFrom sTorFrom;

	sTorFrom.setX(112);

	int safe = -1;

	sTorFrom.saveTo(safe);

	sTorFrom.restoreFrom(safe);

	out << "Restored from safe : " << sTorFrom.getX() << endl;


	WR wr1;
	WR wr2;

	QTextStream in(stdin);

	//in >> wr1 >> wr2;

	//out << wr1 << wr2 << endl;

	NonAssigner nas;

	unsigned int tmp = 10;

	nas = tmp;

	QString tmpStr = "Hello";

	try {

		Message<> msg("Hurrey!!! Custom exception!!!");

		throw ErrMsgException<Message<>>(msg);
		//Message<> ("MessageTest");

		//{
		//	Deleter deleter("Hello");
		//}


	} catch (MsgException<Message<>>&e) {

		out << e.getMsg().getMsgData() << endl;
		out << "Caught exception!" << endl;

	}

	Additor add1;
	Additor add2;

	add1.x = 10;
	add2.x = 20;

	Additor add3 = add1 + add2;
	add3 = add3 + 1;

	out << "Result of addition : " << add3.x << endl;

	add3 = add3 - 2;

	out << "Result of subtraction : " << add3.x << endl;

	add3 = add3 * 10;

	out << "Result of multiplication : " << add3.x << endl;

	add3 = add3 / 5.0;

	out << "Result of division : " << add3.x << endl;

	Inv inv;
	inv.x = 0.0;
	try {
		inv.inv();
	} catch (ErrMsgException<MessageWritableTo<QTextStream>>&e) {
		//} catch (MsgException<MessageWritableTo<QTextStream>>&e) {
		//} catch (Exception<>&e) {

		out << e.getMsg() << endl;
		out << "Exception caught!" << endl;

	}

	out << "Result of inversion : " << inv.x << endl;

	SomeClonable1 sc11;
	sc11.name = "sc11";
	out << sc11.type << endl;

	SomeClonable1* sc12 = sc11.clone();
	sc12->name = "sc12";
	out << sc12->type << endl;

	delete sc12;

	SomeClonable2 sc21;
	out << sc21.type << endl;

	Clonable* cl11 = &sc11;

	Clonable* cl12 = cl11->clone();

	out << ((SomeClonable1*) cl12)->type << endl;

	{



		SomeClonable1* sc1 = new SomeClonable1;
		SomeClonable2* sc2 = new SomeClonable2;

		sc1->name = "cs1";
		sc2->name = "cs2";

		SmartPointer<SomeClonable1> sptr1(sc1);
		SmartPointer<SomeClonable2> sptr2(sc2);

		SmartPointer<SomeClonable1> sptr11;

		try {

			//sptr11 = sptr1;

			//sptr1.setPointer(sc1, true);
			//sptr1.setPointer(sc2, true);

			if (sptr1 == sptr2) {
				out << "sptr1 == sptr2" << endl;
			} else {
				out << "sptr1 != sptr2" << endl;
			}

			out << "SmartPointer : " << sptr1->name << " " << sptr1->type << endl;
			out << "SmartPointer : " << sptr2->name << " " << sptr2->type << endl;

			//out << "SmartPointer sptr11 : " << sptr11->name << " " << sptr11->type << endl;

		} catch (MsgException<Message<>> &e) {

			out << "Source of exception : " << dynamic_cast<SmartPointer<SomeClonable1>*> (e.getSender()) << endl;

			out << e.getMsg().getMsgData() << endl;

			exit(-1);

		}

	}

	out << "Max test : " << Math::max(1, 2) << endl;
	out << "Max test : " << Math::max(1.5, 2.6) << endl;
	out << "Min test : " << Math::min(1, 2) << endl;
	out << "Min test : " << Math::min(1.5, 2.6) << endl;

	QVector<double> someDVector;
	someDVector << 1 << 2 << 3 << 4 << 5.0;

	out << "Min test vector : " << Math::min(someDVector) << endl;
	out << "Max test vector : " << Math::max(someDVector) << endl;

	Math::randPermut(someDVector);

	Math::nextLexPermutation(someDVector);

	for (int i = 0; i < someDVector.size(); i++) {
		out << someDVector[i] << ",";
	}
	out << endl;


	RandGenMT rgmt(1872638163);

	for (int i = 0; i < 10000; i++) {
		out << rgmt.rndFloat() << endl;
	}

	unsigned int numRndClasses = 10;
	unsigned int numRndTests = 5000000;
	vector<double> testFreqs(numRndClasses);

	for (unsigned int i = 0; i < numRndClasses; i++) {
		testFreqs[i] = 0;
	}
	for (unsigned int i = 0; i < numRndTests; i++) {
		unsigned int curIdx = rgmt.rndInt(1, numRndClasses);

		testFreqs[curIdx - 1]++;
	}
	double sumFreq = 0.0;
	for (unsigned int i = 0; i < numRndClasses; i++) {
		testFreqs[i] /= double(numRndTests);

		sumFreq += testFreqs[i];

		out << testFreqs[i] << " ";
	}
	out << endl;
	out << "sumFreq : " << sumFreq << endl;

	out << "Size of unsigned int : " << sizeof (long int) << endl;

	out << "MAX_INT : " << Math::MAX_INT << endl;
	out << "MIN_INT : " << Math::MIN_INT << endl;
	out << "MAX_UINT : " << Math::MAX_UINT << endl;
	out << "MIN_UINT : " << Math::MIN_UINT << endl;
	out << "MAX_INT64 : " << Math::MAX_INT64 << endl;
	out << "MIN_INT64 : " << Math::MIN_INT64 << endl;
	out << "MAX_UINT64 : " << Math::MAX_UINT64 << endl;
	out << "MIN_UINT64 : " << Math::MIN_UINT64 << endl;
	out << "MAX_INT16 : " << Math::MAX_INT16 << endl;
	out << "MIN_INT16 : " << Math::MIN_INT16 << endl;
	out << "MAX_UINT16 : " << Math::MAX_UINT16 << endl;
	out << "MIN_UINT16 : " << Math::MIN_UINT16 << endl;
	out << "maxGenInt : " << rgmt.getMaxGenInt() << endl;

	for (int i = 0; i < 5; ++i) {
		out << i << endl;
	}
	{
		int i = 10;
		foo(&i);
		out << "i = " << i << endl;
	}

	senderReceiverTest();

	//throw ErrException();

	ThreadRunnable tr1;
	//ThreadRunnable tr2;

	tr1.setObjectName("tr 1");
	//tr2.setObjectName("tr 2");

	//tr1.run();
	//tr2.run();

	//QObject::connect(&tr1, SIGNAL(sigFinished()), &app, SLOT(quit()));
	//QObject::connect(&tr2, SIGNAL(sigFinished()), &app, SLOT(quit()));


	return 0; //app.exec();
}
