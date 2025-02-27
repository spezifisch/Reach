#pragma once

#include <JuceHeader.h>
// These will improve the readability of the connection definition

#define getT(Idx) template get<Idx>()
#define connectT(Idx, target) template connect<Idx>(target)
#define getParameterT(Idx) template getParameter<Idx>()
#define setParameterT(Idx, value) template setParameter<Idx>(value)
#define setParameterWT(Idx, value) template setWrapParameter<Idx>(value)
using namespace scriptnode;
using namespace snex;
using namespace snex::Types;

namespace Chorus2_impl
{
// =============================| Node & Parameter type declarations |=============================

DECLARE_PARAMETER_RANGE_SKEW(dry_wet_mixer_c0Range, 
                             -100., 
                             0., 
                             5.42227);

using dry_wet_mixer_c0 = parameter::from0To1<core::gain, 
                                             0, 
                                             dry_wet_mixer_c0Range>;

using dry_wet_mixer_c1 = dry_wet_mixer_c0;

using dry_wet_mixer_multimod = parameter::list<dry_wet_mixer_c0, dry_wet_mixer_c1>;

using dry_wet_mixer_t = control::xfader<dry_wet_mixer_multimod, faders::linear>;

using dry_path_t = container::chain<parameter::empty, 
                                    wrap::fix<2, dry_wet_mixer_t>, 
                                    core::gain>;

using wet_path_t = container::chain<parameter::empty, 
                                    wrap::fix<2, jdsp::jchorus>, 
                                    core::gain>;

namespace dry_wet1_t_parameters
{
}

using dry_wet1_t = container::split<parameter::plain<Chorus2_impl::dry_wet_mixer_t, 0>, 
                                    wrap::fix<2, dry_path_t>, 
                                    wet_path_t>;

namespace Chorus2_t_parameters
{
// Parameter list for Chorus2_impl::Chorus2_t ----------------------------------------------------

DECLARE_PARAMETER_RANGE(CentreDelayRange, 
                        0., 
                        100.);

using CentreDelay = parameter::from0To1<jdsp::jchorus, 
                                        0, 
                                        CentreDelayRange>;

DECLARE_PARAMETER_RANGE(FeedbackRange, 
                        -1., 
                        1.);

using Feedback = parameter::from0To1<jdsp::jchorus, 
                                     2, 
                                     FeedbackRange>;

DECLARE_PARAMETER_RANGE_SKEW(RateRange, 
                             0., 
                             100., 
                             0.30103);

using Rate = parameter::from0To1<jdsp::jchorus, 
                                 3, 
                                 RateRange>;

using Chorus = parameter::empty;
using Depth = parameter::plain<jdsp::jchorus, 1>;
using Mix = parameter::plain<Chorus2_impl::dry_wet1_t, 
                             0>;
using Chorus2_t_plist = parameter::list<Chorus, 
                                        CentreDelay, 
                                        Depth, 
                                        Feedback, 
                                        Rate, 
                                        Mix>;
}

using Chorus2_t_ = container::chain<Chorus2_t_parameters::Chorus2_t_plist, 
                                    wrap::fix<2, dry_wet1_t>>;

// ================================| Root node initialiser class |================================

struct instance: public Chorus2_impl::Chorus2_t_
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(Chorus2);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(98)
		{
			0x005B, 0x0000, 0x4300, 0x6F68, 0x7572, 0x0073, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x015B, 0x0000, 0x4300, 0x6E65, 0x7274, 0x4465, 0x6C65, 0x7961, 
            0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 
            0x003F, 0x0000, 0x5B00, 0x0002, 0x0000, 0x6544, 0x7470, 0x0068, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x035B, 0x0000, 0x4600, 0x6565, 0x6264, 0x6361, 
            0x006B, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 
            0x3F80, 0x0000, 0x0000, 0x045B, 0x0000, 0x5200, 0x7461, 0x0065, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x3F80, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x055B, 0x0000, 0x4D00, 0x7869, 0x0000, 0x0000, 
            0x0000, 0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 0x003F, 0x0000, 
            0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -----------------------------------------------------------------------
		
		auto& dry_wet1 = this->getT(0);                      // Chorus2_impl::dry_wet1_t
		auto& dry_path = this->getT(0).getT(0);              // Chorus2_impl::dry_path_t
		auto& dry_wet_mixer = this->getT(0).getT(0).getT(0); // Chorus2_impl::dry_wet_mixer_t
		auto& dry_gain = this->getT(0).getT(0).getT(1);      // core::gain
		auto& wet_path = this->getT(0).getT(1);              // Chorus2_impl::wet_path_t
		auto& jchorus = this->getT(0).getT(1).getT(0);       // jdsp::jchorus
		auto& wet_gain = this->getT(0).getT(1).getT(1);      // core::gain
		
		// Parameter Connections -----------------------------------------------------------------
		
		dry_wet1.getParameterT(0).connectT(0, dry_wet_mixer); // DryWet -> dry_wet_mixer::Value
		
		this->getParameterT(1).connectT(0, jchorus); // CentreDelay -> jchorus::CentreDelay
		
		this->getParameterT(2).connectT(0, jchorus); // Depth -> jchorus::Depth
		
		this->getParameterT(3).connectT(0, jchorus); // Feedback -> jchorus::Feedback
		
		this->getParameterT(4).connectT(0, jchorus); // Rate -> jchorus::Rate
		
		this->getParameterT(5).connectT(0, dry_wet1); // Mix -> dry_wet1::DryWet
		
		// Modulation Connections ----------------------------------------------------------------
		
		auto& dry_wet_mixer_p = dry_wet_mixer.getWrappedObject().getParameter();
		dry_wet_mixer_p.getParameterT(0).connectT(0, dry_gain); // dry_wet_mixer -> dry_gain::Gain
		dry_wet_mixer_p.getParameterT(1).connectT(0, wet_gain); // dry_wet_mixer -> wet_gain::Gain
		
		// Default Values ------------------------------------------------------------------------
		
		; // dry_wet1::DryWet is automated
		
		; // dry_wet_mixer::Value is automated
		
		;                               // dry_gain::Gain is automated
		dry_gain.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                             // jchorus::CentreDelay is automated
		;                             // jchorus::Depth is automated
		;                             // jchorus::Feedback is automated
		;                             // jchorus::Rate is automated
		jchorus.setParameterT(4, 1.); // jdsp::jchorus::Mix
		
		;                               // wet_gain::Gain is automated
		wet_gain.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 1.);
		this->setParameterT(1, 1.);
		this->setParameterT(2, 1.);
		this->setParameterT(3, 1.);
		this->setParameterT(4, 1.);
		this->setParameterT(5, 1.);
	}
	
	static constexpr bool hasTail() { return true; };
};
}

#undef getT
#undef connectT
#undef setParameterT
#undef setParameterWT
#undef getParameterT
// =====================================| Public Definition |=====================================

namespace project
{
using Chorus2 = wrap::node<Chorus2_impl::instance>;
}


