#include "codingsound.h"

int main()
{
	BASS_Init( 0, 44100, 0, 0, 0 );
	
	CodingSong *song = new CodingSong( 125.0, 128, 4 );
	UltraHat *hat = new UltraHat( 2000 );
	UltraSinus *usine = new UltraSinus();
	CodingXDrum *xd = new CodingXDrum();
	UltraSaw *saw = new UltraSaw( 1.0, song->get16(3) );
	FromFile *sing1 = new FromFile( "singed1.wav" );
	FromFile *sing2 = new FromFile( "singed2.wav" );
	FromFile *sing3 = new FromFile( "singed3.wav" );
	FromFile *clap = new FromFile( "claped.wav" );
	
	int c;
	int na;
	int nb;
	int nc;
	na = 12;
	nb = 48;
	nc = 0;
	
	float sg;
	sg = 0.01;
	int ln;
	float h2g;
	h2g = 0.2;
	float pg;
	pg = 0.75;
	
	while( song->getC() < song->getN() )
	{
		c = song->getC();

		if( sg < 0.4 )
			sg *= 1.01;
		
		if( c%16 == 0 )
		{
			usine->Sinus( song->getL(), 36, sg, song->get16(3) );
			usine->Sinus( song->getR(), 36, sg, song->get16(3) );
		}
		if( c%16 == 3 )
		{
			usine->Sinus( song->getL(), 31, sg, song->get16(2) );
			usine->Sinus( song->getR(), 31, sg, song->get16(2) );
		}
		if( c%16 == 6 )
		{
			usine->Sinus( song->getL(), 32, sg, song->get16(6) );
			usine->Sinus( song->getR(), 32, sg, song->get16(6) );
		}
		if( c%64 == 60 )
		{
			usine->Sinus( song->getL(), 39, sg, song->get16(4) );
			usine->Sinus( song->getR(), 39, sg, song->get16(4) );
		}
		
		if( c >= 1024 )
		{
			if( c%16 == 0 )
			{
				usine->Sinus( song->getL(), 39, sg, song->get16(3) );
				usine->Sinus( song->getR(), 39, sg, song->get16(3) );
			}
			if( c%16 == 3 )
			{
				usine->Sinus( song->getL(), 34, sg, song->get16(2) );
				usine->Sinus( song->getR(), 34, sg, song->get16(2) );
			}
			if( c%16 == 6 )
			{
				usine->Sinus( song->getL(), 36, sg, song->get16(6) );
				usine->Sinus( song->getR(), 36, sg, song->get16(6) );
			}
			if( c%64 == 60 )
			{
				usine->Sinus( song->getL(), 43, sg, song->get16(4) );
				usine->Sinus( song->getR(), 43, sg, song->get16(4) );
			}
		}
		
		if( c%16 == 3 || c%16 == 6 )
		{
			xd->BassDrumSoft( song->getL(), 0.5 );
			xd->BassDrumSoft( song->getR(), 0.5 );
		}
		if( c%4 == 2 && c >= 256 )
		{
			hat->Hat( song->getL(), 40, 0.15, song->get16(1) );
			hat->Hat( song->getR(), 40, 0.15, song->get16(1) );
			hat->Hat( song->getL(), 43, 0.15, song->get16(1) );
			hat->Hat( song->getR(), 43, 0.15, song->get16(1) );
			hat->Hat( song->getL(), 44, 0.15, song->get16(1) );
			hat->Hat( song->getR(), 44, 0.15, song->get16(1) );
			hat->Hat( song->getL(), 47, 0.15, song->get16(1) );
			hat->Hat( song->getR(), 47, 0.15, song->get16(1) );
		}
		

		if( c%16 == 15 )
		{
			saw->Saw( song->getL(), 7, 0.3, song->get16(1) );
			saw->Saw( song->getR(), 7, 0.3, song->get16(1) );
		}
		if( c%16 == 2 )
		{
			saw->Saw( song->getL(), 7, 0.2, song->get16(2) );
			saw->Saw( song->getR(), 7, 0.2, song->get16(2) );
		}
		if( c >= 255 )
		{
			if( c%64 == 22 )
			{
				saw->Saw( song->getL(), 31, 0.1, song->get16(1) );
				saw->Saw( song->getR(), 31, 0.1, song->get16(1) );
			}
			if( c%64 == 24 )
			{
				saw->Saw( song->getL(), 32, 0.1, song->get16(1) );
				saw->Saw( song->getR(), 32, 0.1, song->get16(1) );
			}
			if( c%64 == 26 )
			{
				saw->Saw( song->getL(), 36, 0.1, song->get16(2) );
				saw->Saw( song->getR(), 36, 0.1, song->get16(2) );
			}
			if( c%64 == 28 )
			{
				saw->Saw( song->getL(), 48, 0.1, song->get16(2) );
				saw->Saw( song->getR(), 48, 0.1, song->get16(2) );
			}
			if( c%64 == 30 )
			{
				saw->Saw( song->getL(), 51, 0.1, song->get16(1) );
				saw->Saw( song->getR(), 51, 0.1, song->get16(1) );
			}
		}
		if( c >= 512 )
		{
			if( c%8 == 4 )
				clap->MixFX( song->getL(), song->getR(), 0.2, 15 );
			if( c%32 == 0 )
				sing2->MixFX( song->getL(), song->getR(), 0.3, 27 );
			if( c%32 == 16 )
				sing3->MixFX( song->getL(), song->getR(), 0.35, 27 );
		}
		
		if( c < 1024 || c >= 1520 )
		{
			if( c%16 == 8 )
				sing1->MixFX( song->getL(), song->getR(), 0.4, 15 );
		}
		
		if( c%64 == 0 )
		{
			fputs( "-", stdout );
			fflush( stdout );
		}
		
		song->next();
	}

	song->reset(4);
	while( song->getC() < song->getN() )
	{
		c = song->getC();

		if( c%4 == 0 && c < 1280 )
		{
			xd->BassDrum( song->getL(), 0.8 );
			xd->BassDrum( song->getR(), 0.8 );
		}
		if( c%4 == 0 && c >= 1536 )
		{
			xd->BassDrum( song->getL(), 0.8 );
			xd->BassDrum( song->getR(), 0.8 );
		}
		
		if( c%64 == 0 )
		{
			fputs( "-", stdout );
			fflush( stdout );
		}
		
		song->next();
	}

	song->toFile( "xtrakraas.raw" );

	return 0;
}
