/* 
 * File:   RandomExt.h
 * Author: DrSobik
 *
 * Created on April 7, 2014, 12:35 PM
 */

#ifndef RANDOMEXT_H
#define	RANDOMEXT_H

#include "DebugExt.h"

#include <QObject>
#include <QList>

#include <math.h>

using namespace std;

namespace Common {

#ifndef WINDOWS // WTF: There is a bug in MSVC++ 2010 compiler which DOES NOT handle correctly virtual multiple inheritance!!!

	/** Basic class for all random generators */
	class RandGen : public QObject {
		Q_OBJECT
	private:

		QList<quint32> seeds;

	protected:

		RandGen();

		RandGen(const RandGen& orig);

		RandGen(const QList<quint32>&);

		virtual void init();

		virtual RandGen* clone() = 0;
		
	public:

		virtual ~RandGen();

		void setSeeds(const QList<quint32>& seeds);

		QList<quint32> getSeeds();

	};

	/** Basic class for all integer random number generators */
	class IntRandGen : public virtual RandGen {
		//Q_OBJECT
	private:


	protected:

		IntRandGen();

		IntRandGen(const IntRandGen& orig);

		IntRandGen(const QList<quint32>& seeds);

		virtual void init();

        virtual IntRandGen* clone() = 0;
		
	public:

		const quint32 maxGenInt;

		virtual ~IntRandGen();

		/** Generate a random integer out of [0, 2^32]-1. */
		virtual quint32 rndInt() = 0;

		/** Generate a random integer out of [a,b]. */
		quint32 rndInt(const quint32& a, const quint32& b);

	};

	/** Basic class for all float random number generators */
	class FloatRandGen : public virtual RandGen {
		//Q_OBJECT

	private:

	protected:

		FloatRandGen();

		FloatRandGen(const FloatRandGen& orig);

		FloatRandGen(const QList<quint32>& seeds);

		virtual void init();

        virtual FloatRandGen* clone() = 0;
		
	public:

		virtual ~FloatRandGen();

		/** Generate a random float out of [0, 1]. */
		virtual double rndFloat() = 0;

		/** Generate a random integer out of [a,b]. */
		double rndFloat(const double& a, const double& b);

	};

	/** Basic class for all random number generators */
    class GeneralRandGen : public IntRandGen, public FloatRandGen {
		//Q_OBJECT
	private:

	protected:

		GeneralRandGen();

		GeneralRandGen(const GeneralRandGen& orig);

		GeneralRandGen(const QList<quint32>& seeds);

		virtual void init();
		
	public:

		virtual ~GeneralRandGen();

        virtual GeneralRandGen* clone() = 0;
		
		/** Generate a random integer out of [0, 2^32]-1. */
		virtual quint32 rndInt() = 0;

		quint32 rndInt(const quint32& a, const quint32& b);

		/** Generate a random float out of [0, 1]. */
		virtual double rndFloat();

		double rndFloat(const double& a, const double& b);

	};

#endif

#ifdef WINDOWS

    /** Basic class for all random number generators */
    class GeneralRandGen : public QObject {
        Q_OBJECT
    private:

        QList<quint32> seeds;

    protected:

        GeneralRandGen();

        GeneralRandGen(const GeneralRandGen& orig);

        GeneralRandGen(const QList<quint32>& seeds);

        virtual void init();

    public:

        const quint32 maxGenInt;

        virtual ~GeneralRandGen();

        virtual GeneralRandGen* clone() = 0;

        void setSeeds(const QList<quint32>& seeds);

        QList<quint32> getSeeds();

        /** Generate a random integer out of [0, 2^32]-1. */
        virtual quint32 rndInt() = 0;

        quint32 rndInt(const quint32& a, const quint32& b);

        /** Generate a random float out of [0, 1]. */
        virtual double rndFloat() = 0;

        double rndFloat(const double& a, const double& b);

    };

#endif

	/** Random number generator based on the Mersenne Twister algorithm MT19937. */
	class RandGenMT : public GeneralRandGen {
		//Q_OBJECT
	private:

		quint32 MT [624];
		quint32 idx; // Initial value = 0

	protected:

		RandGenMT();

		virtual void init();
		
	public:

		RandGenMT(const RandGenMT& orig);

		RandGenMT(const QList<quint32>& seeds);
		
		RandGenMT(const quint32& seed);

		virtual ~RandGenMT();

		virtual GeneralRandGen* clone();
		
		void setSeed(const quint32& seed);

		void generateNumbers();

		quint32 rndInt(const quint32& a, const quint32& b);

		/** Generate a random integer out of [0, 2^32]-1 using the MT19937 algorithm. */
		virtual quint32 rndInt();

		double rndFloat(const double& a, const double& b);

		virtual double rndFloat();

	};

	/** Random number generator based on the LCG algorithm from NewLib. */
	class RandGenLCGNL : public GeneralRandGen {
		//Q_OBJECT
	private:

		const quint64 a;
		const quint64 c;
		const quint64 m;

		quint64 X;

	protected:

		RandGenLCGNL();

		virtual void init();
		
	public:

		RandGenLCGNL(const RandGenLCGNL& orig);

		RandGenLCGNL(const QList<quint32>& seeds);
		
		RandGenLCGNL(const quint32& seed);

		virtual ~RandGenLCGNL();

		virtual GeneralRandGen* clone();
		
		void setSeed(const quint32& seed);

		quint32 rndInt(const quint32& a, const quint32& b);

		/** Generate a random integer out of [0, 2^32]-1. */
		virtual quint32 rndInt();

		double rndFloat(const double& a, const double& b);

		virtual double rndFloat();

	};

}

#endif	/* RANDOMEXT_H */

