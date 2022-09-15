# [doc = "Register `LOOPCNT` reader"] pub struct R (crate :: R < LOOPCNT_SPEC >) ; impl core :: ops :: Deref for R { type Target = crate :: R < LOOPCNT_SPEC > ; # [inline (always)] fn deref (& self) -> & Self :: Target { & self . 0 } } impl From < crate :: R < LOOPCNT_SPEC > > for R { # [inline (always)] fn from (reader : crate :: R < LOOPCNT_SPEC >) -> Self { R (reader) } } # [doc = "Register `LOOPCNT` writer"] pub struct W (crate :: W < LOOPCNT_SPEC >) ; impl core :: ops :: Deref for W { type Target = crate :: W < LOOPCNT_SPEC > ; # [inline (always)] fn deref (& self) -> & Self :: Target { & self . 0 } } impl core :: ops :: DerefMut for W { # [inline (always)] fn deref_mut (& mut self) -> & mut Self :: Target { & mut self . 0 } } impl From < crate :: W < LOOPCNT_SPEC > > for W { # [inline (always)] fn from (writer : crate :: W < LOOPCNT_SPEC >) -> Self { W (writer) } } # [doc = "Field `ITER_LEFT` reader - 7:0\\]
Internal. Only to be used through TI provided API."] pub type ITER_LEFT_R = crate :: FieldReader < u8 , u8 > ; # [doc = "Field `ITER_LEFT` writer - 7:0\\]
Internal. Only to be used through TI provided API."] pub type ITER_LEFT_W < 'a , const O : u8 > = crate :: FieldWriter < 'a , u32 , LOOPCNT_SPEC , u8 , u8 , 8 , O > ; # [doc = "Field `RESERVED8` reader - 31:8\\]
Internal. Only to be used through TI provided API."] pub type RESERVED8_R = crate :: FieldReader < u32 , u32 > ; # [doc = "Field `RESERVED8` writer - 31:8\\]
Internal. Only to be used through TI provided API."] pub type RESERVED8_W < 'a , const O : u8 > = crate :: FieldWriter < 'a , u32 , LOOPCNT_SPEC , u32 , u32 , 24 , O > ; impl R { # [doc = "Bits 0:7 - 7:0\\]
Internal. Only to be used through TI provided API."] # [inline (always)] pub fn iter_left (& self) -> ITER_LEFT_R { ITER_LEFT_R :: new ((self . bits & 0xff) as u8) } # [doc = "Bits 8:31 - 31:8\\]
Internal. Only to be used through TI provided API."] # [inline (always)] pub fn reserved8 (& self) -> RESERVED8_R { RESERVED8_R :: new (((self . bits >> 8) & 0x00ff_ffff) as u32) } } impl W { # [doc = "Bits 0:7 - 7:0\\]
Internal. Only to be used through TI provided API."] # [inline (always)] pub fn iter_left (& mut self) -> ITER_LEFT_W < 0 > { ITER_LEFT_W :: new (self) } # [doc = "Bits 8:31 - 31:8\\]
Internal. Only to be used through TI provided API."] # [inline (always)] pub fn reserved8 (& mut self) -> RESERVED8_W < 8 > { RESERVED8_W :: new (self) } # [doc = "Writes raw bits to the register."] # [inline (always)] pub unsafe fn bits (& mut self , bits : u32) -> & mut Self { self . 0 . bits (bits) ; self } } # [doc = "Internal. Only to be used through TI provided API.\n\nThis register you can [`read`](crate::generic::Reg::read), [`write_with_zero`](crate::generic::Reg::write_with_zero), [`reset`](crate::generic::Reg::reset), [`write`](crate::generic::Reg::write), [`modify`](crate::generic::Reg::modify). See [API](https://docs.rs/svd2rust/#read--modify--write-api).\n\nFor information about available fields see [loopcnt](index.html) module"] pub struct LOOPCNT_SPEC ; impl crate :: RegisterSpec for LOOPCNT_SPEC { type Ux = u32 ; } # [doc = "`read()` method returns [loopcnt::R](R) reader structure"] impl crate :: Readable for LOOPCNT_SPEC { type Reader = R ; } # [doc = "`write(|w| ..)` method takes [loopcnt::W](W) writer structure"] impl crate :: Writable for LOOPCNT_SPEC { type Writer = W ; } # [doc = "`reset()` method sets LOOPCNT to value 0"] impl crate :: Resettable for LOOPCNT_SPEC { # [inline (always)] fn reset_value () -> Self :: Ux { 0 } }