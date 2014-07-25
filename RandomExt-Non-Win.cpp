/* 
 * File:   RandomExt.cpp
 * Author: DrSobik
 * 
 * Created on April 7, 2014, 12:35 PM
 */

#include <QtCore/qtextstream.h>

#include "RandomExt.h"

namespace Common {

	/* #########################  RandGen  ################################## */

	RandGen::RandGen() : QObject(0) {

	}

	RandGen::RandGen(const RandGen& orig) : QObject(0) {
		seeds = orig.seeds;
	}

	RandGen::RandGen(const QList<quint32>&) { // Initialize the generator
		//Debugger::info << "RandGen::RandGen : Creating!" << ENDL;
	}

	RandGen::~RandGen() {

	}

	void RandGen::init() {
		Debugger::err << "RandGen::init : Not implemented!!!" << ENDL;
	}

	void RandGen::setSeeds(const QList<quint32>& seeds) {
		this->seeds = seeds;
		init();
	}

	QList<quint32> RandGen::getSeeds() {
		return this->seeds;
	}

	/* ###################################################################### */

	/* ########################  IntRandGen  ################################ */

	IntRandGen::IntRandGen() : maxGenInt(quint32((quint64(2) << 31) - 1)) {

	}

	IntRandGen::IntRandGen(const IntRandGen& orig) : RandGen(orig), maxGenInt(quint32((quint64(2) << 31) - 1)) {

	}

	IntRandGen::IntRandGen(const QList<quint32>& seeds) : RandGen(seeds), maxGenInt(quint32((quint64(2) << 31) - 1)) { // Initialize the generator
		//Debugger::info << "IntRandGen::RandGen : Creating!" << ENDL;
	}

	void IntRandGen::init() {
		Debugger::err << "IntRandGen::init : Not implemented!!!" << ENDL;
	}

	IntRandGen::~IntRandGen() {

	}

	/** Generate a random integer out of [a,b]. */
	quint32 IntRandGen::rndInt(const quint32& a, const quint32& b) {

		//QTextStream out(stdout);

		quint32 rndInteger = rndInt();

		//out << "IntRandGen::rndInt(const quint32& a, const quint32& b) " << a << "," << b << ", " << rndInteger << endl;

		quint32 res = a + (quint32) qRound64(double (rndInteger) / double (maxGenInt) * double (b - a));

		//out << "IntRandGen::rndInt(const quint32& a, const quint32& b) result " << res << endl;

		return res;
	}

	/* ###################################################################### */

	/* ######################  FloatRandGen  ################################ */

	FloatRandGen::FloatRandGen() : RandGen() {

	}

	FloatRandGen::FloatRandGen(const FloatRandGen& orig) : RandGen(orig) {

	}

	FloatRandGen::FloatRandGen(const QList<quint32>& seeds) : RandGen(seeds) { // Initialize the generator
		//Debugger::info << "FloatRandGen::RandGen : Creating!" << ENDL;
	}

	void FloatRandGen::init() {
		Debugger::err << "FloatRandGen::init : Not implemented!!!" << ENDL;
	}

	FloatRandGen::~FloatRandGen() {

	}

	/** Generate a random integer out of [a,b]. */
	double FloatRandGen::rndFloat(const double& a, const double& b) {
		return a + (b - a) * rndFloat();
	}

	/* ###################################################################### */

	/* ######################  GeneralRandGen  ############################## */

	GeneralRandGen::GeneralRandGen() : IntRandGen(), FloatRandGen() {

	}

	GeneralRandGen::GeneralRandGen(const GeneralRandGen& orig) : RandGen(orig), IntRandGen(orig), FloatRandGen(orig) {

	}

	GeneralRandGen::GeneralRandGen(const QList<quint32>& seeds) : RandGen(seeds), IntRandGen(seeds), FloatRandGen(seeds) { // Initialize the generator
		//Debugger::info << "GeneralRandGen::RandGen : Creating!" << ENDL;
	}

	void GeneralRandGen::init() {
		//Debugger::err << "GeneralRandGen::init : Not implemented!" << ENDL;
	}

	GeneralRandGen::~GeneralRandGen() {

	}

	quint32 GeneralRandGen::rndInt(const quint32& a, const quint32& b) {
		return IntRandGen::rndInt(a, b);
	}

	/** Generate a random float out of [0, 1]. */
	double GeneralRandGen::rndFloat() {
		return ((double) rndInt()) / double(IntRandGen::maxGenInt);
	}

	double GeneralRandGen::rndFloat(const double& a, const double& b) {
		return FloatRandGen::rndFloat(a, b);
	}

	/* ###################################################################### */

	/* ########################  RandGenMT  ################################# */

	RandGenMT::RandGenMT() : GeneralRandGen(), idx(0) {

	}

	void RandGenMT::init() {

		//Debugger::info << "RanGenMT::init !!!" << ENDL;

		idx = 0;

		QList<quint32> curSeeds = IntRandGen::getSeeds();

		MT[0] = curSeeds[0];

		for (quint32 i = 1; i <= 623; i++) { // loop over each other element
			MT[i] = (1812433253 * (MT[i - 1] ^ ((MT[i - 1] >> 30))) + i) & 0xFFFFFFFF; // 0x6c078965
		}

	}

	RandGenMT::RandGenMT(const RandGenMT& orig) : RandGen(orig), GeneralRandGen(orig) {
		for (int i = 0; i < 624; i++) MT[i] = orig.MT[i];

		idx = orig.idx;
	}

	RandGenMT::RandGenMT(const QList<quint32>& seeds) : RandGen(seeds), GeneralRandGen(seeds) { // Initialize the generator
		setSeeds(seeds);
	}

	RandGenMT::RandGenMT(const quint32& seed) {
		QList<quint32> newSeeds;
		newSeeds << seed;

		setSeed(seed);

	}

	RandGenMT::~RandGenMT() {
		Debugger::info << "RandGenMT::~RandGenMT" << ENDL;
	}

	GeneralRandGen* RandGenMT::clone() {
		return new RandGenMT(*this);
	}

	void RandGenMT::setSeed(const quint32& seed) {
		QList<quint32> newSeeds;
		newSeeds << seed;
		setSeeds(newSeeds);
	}

	void RandGenMT::generateNumbers() {

		for (int i = 0; i <= 623; i++) {
			quint32 y = (MT[i] & 0x80000000) // bit 31 (32nd bit) of MT[i]
					+ (MT[(i + 1) % 624] & 0x7fffffff); // bits 0-30 (first 31 bits) of MT[...]

			MT[i] = MT[(i + 397) % 624] ^ (y >> 1);

			if ((y % 2) != 0) { // y is odd
				MT[i] = MT[i] ^ (2567483615); // 0x9908b0df
			}
		}

	}

	quint32 RandGenMT::rndInt(const quint32& a, const quint32& b) {
		return GeneralRandGen::rndInt(a, b);
	}

	/** Generate a random integer out of [0, 2^32]-1 using the MT19937 algorithm. */
	quint32 RandGenMT::rndInt() {

		if (idx == 0) {
			generateNumbers();
		};

		quint32 y = MT[idx];

		y = y ^ (y >> 11);
		y = y ^ ((y << 7) & (2636928640)); // 0x9d2c5680
		y = y ^ ((y << 15) & (4022730752)); // 0xefc60000
		y = y ^ (y >> 18);

		idx = (idx + 1) % 624;

		return y;
	}

	double RandGenMT::rndFloat(const double& a, const double& b) {
		return GeneralRandGen::rndFloat(a, b);
	}

	double RandGenMT::rndFloat() {
		return GeneralRandGen::rndFloat();
	}

	/* ###################################################################### */

	/* ########################  RandGenMT  ################################# */

	RandGenLCGNL::RandGenLCGNL() : GeneralRandGen(), a(quint64(6364136223846793005)), c(quint64(1)), m(quint64(quint64(2) << 63) - 1), X(0) {

	}

	RandGenLCGNL::RandGenLCGNL(const RandGenLCGNL& orig) : RandGen(orig), GeneralRandGen(orig), a(quint64(6364136223846793005)), c(quint64(1)), m(quint64(quint64(2) << 63) - 1) {
		X = orig.X;
	}

	RandGenLCGNL::RandGenLCGNL(const QList<quint32>& seeds) : RandGen(seeds), GeneralRandGen(seeds), a(quint64(6364136223846793005)), c(quint64(1)), m(quint64(quint64(2) << 63) - 1) {
		setSeeds(seeds);
	}

	RandGenLCGNL::RandGenLCGNL(const quint32& seed) : a(quint64(6364136223846793005)), c(quint64(1)), m(quint64(quint64(2) << 63) - 1), X(0) {
		QList<quint32> newSeeds;
		newSeeds << seed;

		setSeed(seed);

	}

	RandGenLCGNL::~RandGenLCGNL() {

	}

	GeneralRandGen* RandGenLCGNL::clone() {
		return new RandGenLCGNL(*this);
	}

	void RandGenLCGNL::init() {

		//Debugger::info << "RandGenLCGNL::init !!!" << ENDL;

		QList<quint32> curSeeds = getSeeds();

		X = curSeeds[0];

		//Debugger::info << "RandGenLCGNL::seed " << (int) X << ENDL;

		//Debugger::info << "RandGenLCGNL::init finished !!!" << ENDL;

	}

	void RandGenLCGNL::setSeed(const quint32& seed) {
		QList<quint32> newSeeds;
		newSeeds << seed;
		setSeeds(newSeeds);
	}

	quint32 RandGenLCGNL::rndInt(const quint32& a, const quint32& b) {

		//Debugger::info << "RandGenLCGNL::rndInt(a,b) running !!!" << ENDL;

		//exit(-1);

		return GeneralRandGen::rndInt(a, b);
	}

	/** Generate a random integer out of [0, 2^32]-1 using the MT19937 algorithm. */
	quint32 RandGenLCGNL::rndInt() {
		//QTextStream out(stdout); // Comment!!! Otherwise the algorithm is really slow!!!

		//out << "RandGenLCGNL::rndInt() running !!!" << endl;



		X = ((a * X + c) & 0xFFFFFFFFFFFFFFFF) >> 32;

		//X = X+1;

		//out << "a = " << a << endl;
		//out << "m = " << quint64(m) << endl;

		//out << "RandGenLCGNL::rndInt() : maxGenInt : " << maxGenInt << endl;

		//out << "RandGenLCGNL::rndInt() : Value : " << X << endl;

		return X;
	}

	double RandGenLCGNL::rndFloat(const double& a, const double& b) {
		return GeneralRandGen::rndFloat(a, b);
	}

	double RandGenLCGNL::rndFloat() {
		return GeneralRandGen::rndFloat();
	}

	/* ###################################################################### */

}