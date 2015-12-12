class UltraSaw
{
	private:
	double phLFO;
	double incLFO;
	int el;

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

	public:
	UltraSaw( double LFOfreq, int echolen )
	{
		phLFO = 0.0;
		incLFO = DP / SR * LFOfreq;
		el = echolen;
	}

	void Saw( float *out, int note, float vol, int len )
	{
		float freq;
		freq = 27.5*Pitch(note);
		int i;
		int n;
		float s[8];
		for( i = 0; i < 8; i++ )
			s[i] = ( (float)(rand()%100)/50.0 ) - 1.0;
		float sdec;
		sdec = 2.0 / SR * freq;
		float sam;
		float sav;
		float hi;
		hi = 0.0;
		float low;
		low = 0.0;
		float low2;
		low2 = 0.0;
		float v;
		v = 1.0;
		float vdec;
		vdec = 0.15 / 20000.0;
		float q;
		
		for( n = 0; n < len+20000; n++ )
		{
			q = 0.225 + ( 0.195 * sin(phLFO) );
			phLFO += incLFO;
			if( phLFO >= DP )
				phLFO -= DP;
			
			sam = 0.0;
			for( i = 0; i < 8; i++ )
				sam += s[i] / (1.0 + (float)i);
			sav = sam;
			if( s[0] < -0.4 )
				sav -= 0.9;
			else
				sav += 0.9;
			low -= (low - sam) * q;
			sam = low;
			hi += (sam - hi) * q;
			sam -= hi;
			q = (freq * 8.0) / HSR;
			low2 -= (low2 - sam) * q;
			sam = low2 * 3.0;
			sam += sav * 0.1;
			
			out[n] += v * vol * sam;
			out[n+el] += v * vol * sam * 0.2;
			out[n+el+el] += v * vol * sam * 0.125;
			out[n+el+el+el] += v * vol * sam * 0.085;
			out[n+el+el+el+el] += v * vol * sam * 0.025;
			
			if( n > len - 100 && n <= len )
				v -= 0.0085;
			if( n > len )
				v -= vdec;
			
			for( i = 0; i < 8; i++ )
			{
				s[i] -= sdec * (1.0 + (0.0025 * (float)i));
				if( s[i] <= -1.0 )
					s[i] += 2.0;
			}
		}
	}
};
