#include "NumericInput.h"
#include "imgui.h"

// Class IntSlider
void IntSlider::draw()
{
    if (ImGui::SliderInt(std::format("##{}", getName()).c_str(), &value_, attributeint_->getMin(), attributeint_->getMaximum()))
    {
        attributeint_->setValue(value_);
    }
}
//---------------------------------------------------------------------------------------

// Class IntVSSlider
void IntVSSlider::draw()
{
    if (ImGui::VSliderInt(std::format("##{}", getName()).c_str(), ImVec2(20, 50), &value_, attributeint_->getMin(), attributeint_->getMaximum()))
    {
        attributeint_->setValue(value_);
    }
}

//---------------------------------------------------------------------------------------

// Class IntDrag
void IntDrag::draw()
{
    if (ImGui::DragInt(std::format("##{}", getName()).c_str(), &value_, 1.0f, attributeint_->getMin(), attributeint_->getMaximum()))
    {
        attributeint_->setValue(value_);
    }
}





//---------------------------------------------------------------------------------------

// Class DoubleSlider
void DoubleSlider::draw() { ImGui::SliderScalar(getName().c_str(), ImGuiDataType_Double, &value_, &minimum_, &maximum_);}


//---------------------------------------------------------------------------------------

// Class DoubleVSSlider
void DoubleVSSlider::draw() { ImGui::VSliderScalar(getName().c_str(),ImVec2(50,70),ImGuiDataType_Double,&value_, &minimum_, &maximum_); }

//---------------------------------------------------------------------------------------

// Class DoubleDrag
void DoubleDrag::draw() { ImGui::DragScalar(getName().c_str(),ImGuiDataType_Double,&value_,0.5f, &minimum_, &maximum_); }

//--------------------------------------------------------------------------------------



