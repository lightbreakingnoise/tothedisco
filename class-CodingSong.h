class CodingSong
{
	private:
	float BPM;
	float len16;
	int num16;
	int c16;
	int songlen;
	float pos;
	int neben;
	
	public:
	float *left;
	float *right;

	CodingSong( float beats, int takts, int ungenau )
	{
		neben = ungenau;
		BPM = beats;
		len16 = (SR * 15.0) / BPM;
		num16 = 16 * takts;
		c16 = 0;
		songlen = (int)((float)num16 * len16);
		
		songlen += 1000000;
		left = (float*) malloc( sizeof(float) * songlen );
		right = (float*) malloc( sizeof(float) * songlen );
		songlen -= 1000000;
		songlen += (int)SR;
		
		int i;
		for( i = 0; i < songlen; i++ )
		{
			left[i] = 0.0;
			right[i] = 0.0;
		}
		
		pos = 0.0;
	}
	
	int get16( int anz )
	{
		return (int)(len16 * (float)anz);
	}
	
	float *getL()
	{
		return &left[(int)pos+(rand()%neben)];
	}
	
	float *getR()
	{
		return &right[(int)pos+(rand()%neben)];
	}
	
	int getC()
	{
		return c16;
	}
	
	int getN()
	{
		return num16;
	}
	
	float getLFO( float multi )
	{
		return (BPM / 60.0) * multi;
	}
	
	void reset( int ungenau )
	{
		neben = ungenau;
		c16 = 0;
		pos = 0.0;
	}
	
	void next()
	{
		if( c16%2 == 0 )
			pos += len16 * 1.2;
		else
			pos += len16 * 0.8;
		c16++;
	}
	
	void toFile( const char *filename )
	{
		int i;
		float sam;
		float maxl;
		float maxr;
		maxl = 0.5;
		maxr = 0.5;
		float lmul;
		float rmul;
		lmul = 1.0;
		rmul = 1.0;
		float tmp;
		for( i = 0; i < songlen; i++ )
		{
			maxl *= 0.9999;
			sam = left[i];
			if( sam < 0.0 )
				sam = -sam;
			if( sam > maxl )
				maxl = sam;
			if( maxl < 0.4 )
				maxl = 0.4;
			tmp = 0.7 / maxl;
			if( lmul < tmp )
				lmul *= 1.002;
			if( lmul > tmp )
				lmul /= 1.0005;
			left[i] *= lmul;
			if( left[i] < -1.0 ) left[i] = -1.0;
			if( left[i] > 1.0 ) left[i] = 1.0;
			
			maxr *= 0.9999;
			sam = right[i];
			if( sam < 0.0 )
				sam = -sam;
			if( sam > maxr )
				maxr = sam;
			if( maxr < 0.4 )
				maxr = 0.4;
			tmp = 0.7 / maxr;
			if( rmul < tmp )
				rmul *= 1.002;
			if( rmul > tmp )
				rmul /= 1.0005;
			right[i] *= rmul;
			if( right[i] < -1.0 ) right[i] = -1.0;
			if( right[i] > 1.0 ) right[i] = 1.0;
		}
		
		short s;
		FILE *fp;
		fp = fopen( filename, "wb" );
		for( i = 0; i < songlen; i++ )
		{
			s = (short)(left[i] * 32700.0);
			fwrite( &s, 2, 1, fp );
			s = (short)(right[i] * 32700.0);
			fwrite( &s, 2, 1, fp );
		}
		fclose( fp );
	}
};
