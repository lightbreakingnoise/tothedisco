class XGeiger
{
	private:

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
	XGeiger()
	{
	}

	void Geig( float *out, int note, float vol, int len )
	{
		float freq;
		freq = 27.5*Pitch(note);
		int i;
		int n;
		int x;
		float phase[10];
		float inc[10];
		for( n = 0; n < 8; n++ )
		{
			phase[n] = (float)((rand()%1000) / 500.0) - 1.0;
			inc[n] = 2.0 / SR * freq;
			inc[n] *= (1.0 + ((float)(1+n) / 500.0));
		}
		float sph;
		sph = 0.0;
		float sinc;
		sinc = DP / SR * (freq * 0.5);
		float s[20];
		float sam;
		float sec;
		float flt[20];
		for( i = 0; i < 20; i++ )
			flt[i] = 0.0;
		float q;
		float v;
		v = 1.0;
		float vdec;
		vdec = 1.0 / (float)len;
		float hifrq;
		hifrq = freq*8.0;
		
		for( n = 0; n < len; n++ )
		{
			sam = 0.0;
			for( x = 0; x < 8; x++ )
			{
				if( phase[x] < 0.0 )
					sam -= 0.25;
				else
					sam += 0.25;
				sam += phase[x] * 0.6;
			}
			sam += ((float)(rand()%100) / 100.0) - 0.5;
			
			q = hifrq / HSR;
			flt[3] -= (flt[3] - sam) * q;
			sam = flt[3];
			sec = sam;
			q = 2000.0 / HSR;
			flt[0] += (sec - flt[0]) * q;
			sec -= flt[0];
			q = 2500.0 / HSR;
			flt[1] -= (flt[1] - sec) * q;
			sec = flt[1];
			sam += sec;
			
			if( hifrq < 8000.0 )
				hifrq *= 1.000025;
			
			sam *= v * vol * 0.3;
			out[n] += sam;
			
			v -= vdec;
			
			for( x = 0; x < 8; x++ )
			{
				phase[x] += inc[x] + (0.5 * inc[x] * sin(sph));
				if( phase[x] >= 1.0 )
					phase[x] -= 2.0;
			}
			sph += sinc;
		}
	}
};
