# [doc = "Register `LFSR0` reader"] pub struct R (crate :: R < LFSR0_SPEC >) ; impl core :: ops :: Deref for R { type Target = crate :: R < LFSR0_SPEC > ; # [inline (always)] fn deref (& self) -> & Self :: Target { & self . 0 } } impl From < crate :: R < LFSR0_SPEC > > for R { # [inline (always)] fn from (reader : crate :: R < LFSR0_SPEC >) -> Self { R (reader) } } # [doc = "Register `LFSR0` writer"] pub struct W (crate :: W < LFSR0_SPEC >) ; impl core :: ops :: Deref for W { type Target = crate :: W < LFSR0_SPEC > ; # [inline (always)] fn deref (& self) -> & Self :: Target { & self . 0 } } impl core :: ops :: DerefMut for W { # [inline (always)] fn deref_mut (& mut self) -> & mut Self :: Target { & mut self . 0 } } impl From < crate :: W < LFSR0_SPEC > > for W { # [inline (always)] fn from (writer : crate :: W < LFSR0_SPEC >) -> Self { W (writer) } } # [doc = "Field `LFSR_31_0` reader - 31:0\\]
Bits \\[31:0\\]
of the main entropy accumulation LFSR. Register can only be accessed when CTL.TEST_MODE = 1. Register contents will be cleared to zero before access is enabled."] pub type LFSR_31_0_R = crate :: FieldReader < u32 , u32 > ; # [doc = "Field `LFSR_31_0` writer - 31:0\\]
Bits \\[31:0\\]
of the main entropy accumulation LFSR. Register can only be accessed when CTL.TEST_MODE = 1. Register contents will be cleared to zero before access is enabled."] pub type LFSR_31_0_W < 'a , const O : u8 > = crate :: FieldWriter < 'a , u32 , LFSR0_SPEC , u32 , u32 , 32 , O > ; impl R { # [doc = "Bits 0:31 - 31:0\\]
Bits \\[31:0\\]
of the main entropy accumulation LFSR. Register can only be accessed when CTL.TEST_MODE = 1. Register contents will be cleared to zero before access is enabled."] # [inline (always)] pub fn lfsr_31_0 (& self) -> LFSR_31_0_R { LFSR_31_0_R :: new (self . bits) } } impl W { # [doc = "Bits 0:31 - 31:0\\]
Bits \\[31:0\\]
of the main entropy accumulation LFSR. Register can only be accessed when CTL.TEST_MODE = 1. Register contents will be cleared to zero before access is enabled."] # [inline (always)] pub fn lfsr_31_0 (& mut self) -> LFSR_31_0_W < 0 > { LFSR_31_0_W :: new (self) } # [doc = "Writes raw bits to the register."] # [inline (always)] pub unsafe fn bits (& mut self , bits : u32) -> & mut Self { self . 0 . bits (bits) ; self } } # [doc = "LFSR Readout Value\n\nThis register you can [`read`](crate::generic::Reg::read), [`write_with_zero`](crate::generic::Reg::write_with_zero), [`reset`](crate::generic::Reg::reset), [`write`](crate::generic::Reg::write), [`modify`](crate::generic::Reg::modify). See [API](https://docs.rs/svd2rust/#read--modify--write-api).\n\nFor information about available fields see [lfsr0](index.html) module"] pub struct LFSR0_SPEC ; impl crate :: RegisterSpec for LFSR0_SPEC { type Ux = u32 ; } # [doc = "`read()` method returns [lfsr0::R](R) reader structure"] impl crate :: Readable for LFSR0_SPEC { type Reader = R ; } # [doc = "`write(|w| ..)` method takes [lfsr0::W](W) writer structure"] impl crate :: Writable for LFSR0_SPEC { type Writer = W ; } # [doc = "`reset()` method sets LFSR0 to value 0"] impl crate :: Resettable for LFSR0_SPEC { # [inline (always)] fn reset_value () -> Self :: Ux { 0 } }