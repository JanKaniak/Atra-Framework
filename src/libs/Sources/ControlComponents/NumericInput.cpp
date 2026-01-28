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
void DoubleSlider::draw() { 
    if (ImGui::SliderScalar(std::format("##{}", getName()).c_str(), ImGuiDataType_Double, &value_, &minimum_, &maximum_)) {
        attributedouble_->setValue(value_);
    }
}


//---------------------------------------------------------------------------------------

// Class DoubleVSSlider
void DoubleVSSlider::draw() { 
    if (ImGui::VSliderScalar(std::format("##{}", getName()).c_str(),ImVec2(50,70),ImGuiDataType_Double,&value_, &minimum_, &maximum_)) {
        attributedouble_->setValue(value_);
    } 
}

//---------------------------------------------------------------------------------------

// Class DoubleDrag
void DoubleDrag::draw() { if (ImGui::DragScalar(std::format("##{}", getName()).c_str(),ImGuiDataType_Double,&value_,0.5f, &minimum_, &maximum_)) {
        attributedouble_->setValue(value_);
    }
 }

//--------------------------------------------------------------------------------------





//---------------------------------------------------------------------------------------

// Class FloatSlider
void FloatSlider::draw() { if (ImGui::SliderFloat2(std::format("##{}", getName()).c_str(), &value_, minimum_, maximum_)) {
        attributefloat_->setValue(value_);
    }
}


//---------------------------------------------------------------------------------------

// Class FloatVSSlider
void FloatVSSlider::draw() { if (ImGui::VSliderFloat(std::format("##{}", getName()).c_str(),ImVec2(50,70),&value_, minimum_, maximum_)) {
        attributefloat_->setValue(value_);
    }
 }

//---------------------------------------------------------------------------------------

// Class FloatDrag
void FloatDrag::draw() { if (ImGui::DragFloat2(std::format("##{}", getName()).c_str(),&value_,0.5f, minimum_, maximum_)) {
        attributefloat_->setValue(value_);
    }
 }

//--------------------------------------------------------------------------------------



