class XPiSaw
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
	XPiSaw()
	{
	}

	void Saw( float *out, int note, float vol, int len )
	{
		float freq;
		freq = 27.5*Pitch(note);
		int i;
		int n;
		int x;
		float phase;
		phase = -1.0;
		float inc;
		inc = 2.0 / SR * freq;
		float sam;
		float flt[20];
		for( i = 0; i < 20; i++ )
			flt[i] = 0.0;
		float q;
		float v;
		v = 1.0;
		float vdec;
		vdec = 1.0 / (float)len;
		float hifrq;
		hifrq = 8000.0;
		
		for( n = 0; n < len; n++ )
		{
			if( phase < 0.35 )
				sam = -0.45;
			else
				sam = 0.45;
			sam += phase * 0.6;
			
			sam += ((float)(rand()%100) / 200.0) - 0.25;
						
			q = hifrq / HSR;
			flt[2] += (sam - flt[2]) * q;
			sam -= flt[2];
			flt[3] -= (flt[3] - sam) * q;
			sam = flt[3];
			flt[4] += (sam - flt[4]) * q;
			sam -= flt[4];
			flt[5] -= (flt[5] - sam) * q;
			sam = flt[5] * 1.2;
						
			if( hifrq > freq*4.0 )
				hifrq *= 0.997;
						
			sam *= v * v * vol * 4.0;
			out[n] += sam;
			
			v -= vdec;
			
			phase += inc;
			if( phase >= 1.0 )
				phase -= 2.0;
		}
	}
};
