class FromFile
{
	private:
	HSTREAM hstr;
	float *inter;
	short *pcm;
	int len;
	
	float Pitch( int p )
	{
		int i;
		float out;
		out = 1.0;
		
		if( p > 0 )
		{
			for( i = 0; i < p; i++ )
				out /= HN;
		}
		
		if( p < 0 )
		{
			for( i = 0; i > p; i-- )
				out *= HN;
		}
		
		return out;
	}

	float prc( float a, float b, float dist )
	{
		float out;
		float diff;
		
		diff = b - a;
		out = a + (diff*dist);
		
		return out;
	}
	
	public:
	FromFile( const char *filename )
	{
		pcm = (short*) malloc( 2 * sizeof(short) * 441000 ); //allocate 10 seconds
		hstr = BASS_StreamCreateFile( FALSE, filename, 0, 0, BASS_STREAM_DECODE );
				printf( "%d\n", BASS_ErrorGetCode() );
		len = 0;
		int rc;
		while( true )
		{
			rc = BASS_ChannelGetData( hstr, &pcm[len], 5000 );
			if( rc < 0 )
			{
				printf( "%d\n", BASS_ErrorGetCode() );
				break;
			}
			len += rc / 2;
			if( rc != 5000 )
				break;
		}
		inter = (float*) malloc( 2 * sizeof(float) * len );
		int x;
		for( x = 0; x < len; x++ )
			inter[x] = (float)pcm[x] / 32800.0;
		free( pcm );
	}
	
	void Mix( float *left, float *right, float vol )
	{
		int i;
		int x;
		i = 0;
		
		for( x = 0; x < len; x += 2 )
		{
			left[i] += vol * inter[x];
			right[i] += vol * inter[x+1];
			i++;
		}
	}
	
	void MixEcho( float *left, float *right, float vol, int echolen, float echovol )
	{
		int i;
		int x;
		int n;
		float saml;
		float samr;
		float pong;
		float ponginc;
		pong = -0.8;
		ponginc = 0.001;
		float lv;
		float rv;
		i = 0;
		
		for( x = 0; x < len; x += 2 )
		{
			saml = vol * inter[x];
			samr = vol * inter[x+1];
			left[i] += saml;
			right[i] += samr;
			saml *= echovol;
			samr *= echovol;
			for( n = 0; n < 44100*5; n += echolen )
			{
				lv = 1.0;
				rv = 1.0;
				if( pong < 0.0 )
					lv += pong;
				else
					rv -= pong;
				left[i+n] += saml * lv;
				right[i+n] += samr * rv;
				saml *= 0.6;
				samr *= 0.6;
			}
			pong += ponginc;
			if( pong < -0.8 )
				ponginc = 0.001;
			if( pong > 0.8 )
				ponginc = -0.001;
			i++;
		}
	}
	
	void MixFX( float *left, float *right, float vol, int note )
	{
		int i;
		int x;
		i = 0;
		
		float LFO;
		LFO = 27.5*Pitch( note+7 );
		float LF2;
		LF2 = 27.5*Pitch( note );
		
		float saml;
		float samr;
		float sl;
		float sr;
		
		float lol;
		lol = 0.0;
		float lor;
		lor = 0.0;
		float hil;
		hil = 0.0;
		float hir;
		hir = 0.0;
		float blol;
		blol = 0.0;
		float blor;
		blor = 0.0;
		float bhil;
		bhil = 0.0;
		float bhir;
		bhir = 0.0;
		float q;
		float fr;
		double ph;
		ph = 0.0;
		double inc;
		inc = DP / SR * LFO;
		double p2;
		p2 = 0.0;
		double in2;
		in2 = DP / SR * LF2;
		
		for( x = 0; x < len-24; x += 2 )
		{
			saml = vol * inter[x];
			samr = vol * inter[x+1];
			sl = vol * inter[x+22];
			sr = vol * inter[x+23];
			
			fr = 5000.0 + (4800.0 * sin(ph));
			ph += inc + (0.75 * inc * sin(p2));
			p2 += in2;
			
			q = fr / HSR;
			lol -= (lol - saml) * q;
			lor -= (lor - samr) * q;
			saml = lol;
			samr = lor;
			hil += (saml - hil) * q;
			hir += (samr - hir) * q;
			saml -= hil;
			samr -= hir;
			blol -= (blol - saml) * q;
			blor -= (blor - samr) * q;
			saml = blol;
			samr = blor;
			bhil += (saml - bhil) * q;
			bhir += (samr - bhir) * q;
			saml -= bhil;
			samr -= bhir;

			saml = prc( sl, saml*2.5, -0.5 - (0.6*sin(ph)) );
			samr = prc( sr, samr*2.5, -0.5 - (0.6*sin(ph)) );
			
			left[i] += saml;
			right[i] += samr;
			
			i++;
		}
	}
};
