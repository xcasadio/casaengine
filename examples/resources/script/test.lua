function OnScriptInitialize()
-- entity:subscribeEvent("Ticked", "OnTick");
-- CasaEngine.GlobalSetEvent:subscribeEvent("Ticked", "OnTick");
end


function OnTick(elapsedTime)
    local input = CasaEngine.Game:Instance():GetInput();
	
	if input:IsKeyDown(sf.Keyboard.Right) == true then
		entity:GetAnim2DCpnt():SetCurrentAnimation("Anim_belrick_run_r");
		--entity:SetLinearVelocity(Vector3F:Right() * runVelocity);
		
	elseif input:IsKeyDown(sf.Keyboard.Left) == true then
		entity:SetAnim2DCpnt():SetCurrentAnimation("Anim_belrick_run_l");
		--entity:SetLinearVelocity(Vector3F:Left() * runVelocity);
	
	elseif input:IsKeyDown(sf.Keyboard.Up) == true then
		entity:GetAnim2DCpnt():SetCurrentAnimation("Anim_belrick_run_u");
		--entity:SetLinearVelocity(Vector3F:Up() * runVelocity);
	
	elseif input:IsKeyDown(sf.Keyboard.Down) == true then
		entity:GetAnim2DCpnt():SetCurrentAnimation("Anim_belrick_run_d");
		--entity:SetLinearVelocity(Vector3F:Down() * runVelocity);
		
	end
	
	-- RUNNING
--	if input:isRightPressed() == true then
--		entity:GetAnim2DCpnt():SetCurrentAnimation("Anim_belrick_run_r");
--		entity:SetLinearVelocity(Vector3F:Right() * runVelocity);
--		
--	elseif input:isLeftPressed() == true then
--		entity:SetAnim2DCpnt():SetCurrentAnimation("Anim_belrick_run_l");
--		entity:SetLinearVelocity(Vector3F:Left() * runVelocity);
--	
--	elseif input:isUpPressed() == true then
--		entity:GetAnim2DCpnt():SetCurrentAnimation("Anim_belrick_run_u");
--		entity:SetLinearVelocity(Vector3F:Up() * runVelocity);
--	
--	elseif input:isDownPressed() == true then
--		entity:GetAnim2DCpnt():SetCurrentAnimation("Anim_belrick_run_d");
--		entity:SetLinearVelocity(Vector3F:Down() * runVelocity);
--		
--	else
--		
--		entity:SetLinearVelocity(Vector3F:Zero());
--		
--		-- IDLE
--		if (direction() == Right) then
--			entity:GetAnim2DCpnt():SetCurrentAnimation("Anim_belrick_idle_r");
--		
--		elseif (direction() == Left) then
--			entity:GetAnim2DCpnt():SetCurrentAnimation("Anim_belrick_idle_l");
--		
--		elseif (direction() == Up) then
--			entity:GetAnim2DCpnt():SetCurrentAnimation("Anim_belrick_idle_u");
--		
--		elseif (direction() == Down) then
--			entity:GetAnim2DCpnt():SetCurrentAnimation("Anim_belrick_idle_d");
--		
--		end -- if direction
--	
--	end -- if input pressed
	
end -- function tick

local entity;
local runVelocity = 1000;
-- local guiSystem = CEGUI.System:getSingleton()