class UltraPulse
{
	private:
	double phLFO;
	double incLFO;

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
	UltraPulse( double LFOfreq )
	{
		incLFO = DP / SR * LFOfreq;
	}

	void Pulse( float *out, int note, float vol, int len )
	{
		phLFO = 0.0;
		float freq;
		freq = 27.5*Pitch(note);
		int i;
		int n;
		float phase;
		phase = -1.0;
		float inc;
		inc = 2.0 / SR * freq;
		float sam;
		float mid;
		mid = 0.5 - (float)((rand()%10) / 100.0);
		float hi;
		hi = 0.0;
		float hi2;
		hi2 = 0.0;
		float hi3;
		hi3 = 0.0;
		float low;
		low = 0.0;
		float low2;
		low2 = 0.0;
		float low3;
		low3 = 0.0;
		float q;
		
		for( n = 0; n < len; n++ )
		{
			q = 0.05 + ( 0.045 * sin(phLFO) );
			phLFO += incLFO;
			if( phLFO >= DP )
				phLFO -= DP;
			
			if( phase < mid )
				sam = -5.0;
			else
				sam = 5.0;
			
			low -= (low - sam) * (q/1.05);
			sam = low;
			hi += (sam - hi) * (q*1.05);
			sam -= hi;
			low2 -= (low2 - sam) * (q/1.05);
			sam = low2;
			hi2 += (sam - hi2) * (q*1.05);
			sam -= hi2;
			low3 -= (low3 - sam) * (q/1.05);
			sam = low3;
			hi3 += (sam - hi3) * (q*1.05);
			sam -= hi3;
			
			out[n] += vol * sam;
			
			phase += inc;
			if( phase >= 1.0 )
			{
				mid = 0.5 - (float)((rand()%10) / 100.0);
				phase -= 2.0;
			}
		}
	}
};
