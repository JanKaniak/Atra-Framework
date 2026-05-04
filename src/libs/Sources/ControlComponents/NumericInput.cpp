#include "NumericInput.h"

// Class IntSlider
/// Render a horizontal integer slider and apply changed value back to the attribute.
void IntSlider::draw(std::vector<Message> &messageHistory)
{
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }
    
    if (ImGui::SliderScalar(std::format("##{}" ,getName()).c_str(),attribute_->getDescription()->getDataType() ,&value_, &minimum_, &maximum_))
    {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
}

// Class IntVSlider
/// Render a vertical integer slider and synchronize its value with the attribute.
void IntVSlider::draw(std::vector<Message> &messageHistory)
{

    ImVec2 size;
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        size.x = 30;
        size.y = (float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f;
    } else {
        size.x = 30;
        size.y = 100;
    }
    if (ImGui::VSliderScalar(std::format("##{}", getName()).c_str(), ImVec2(30, 100), attribute_->getDescription()->getDataType(),&value_, &minimum_ ,&maximum_))
    {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
}


// Class IntDrag
/// Render an integer drag control and persist changes to the bound attribute.
void IntDrag::draw(std::vector<Message> &messageHistory)
{
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragInt(std::format("##{}", getName()).c_str(), &value_, 1.0f, attribute_->getMinimum(), attribute_->getMaximum()))
    {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
}





//---------------------------------------------------------------------------------------

// Class DoubleSlider
/// Render a horizontal double slider and write back to the attribute when changed.
void DoubleSlider::draw(std::vector<Message> &messageHistory) { 
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }
    
    if (ImGui::SliderScalar(std::format("##{}", getName()).c_str(), attribute_->getDescription()->getDataType(), &value_, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
}




// Class DoubleVSlider
/// Render a vertical double slider and update the attribute on drag.
void DoubleVSlider::draw(std::vector<Message> &messageHistory) {
    ImVec2 size;
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        size.x = 30;
        size.y = (float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f;
    } else {
        size.x = 30;
        size.y = 100;
    }
    if (ImGui::VSliderScalar(std::format("##{}", getName()).c_str(),size,attribute_->getDescription()->getDataType(),&value_, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    } 
    dimensions_ = ImGui::GetItemRectSize();
}



// Class DoubleDrag
/// Render a double-precision drag control and propagate updates to the attribute.
void DoubleDrag::draw(std::vector<Message> &messageHistory) { 
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragScalar(std::format("##{}", getName()).c_str(),attribute_->getDescription()->getDataType(),&value_,0.5f, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
 }

//---------------------------------------------------------------------------------------



// Class FloatSlider
/// Render a horizontal float slider and store the updated value in the attribute.
void FloatSlider::draw(std::vector<Message> &messageHistory) {
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::SliderFloat(std::format("##{}", getName()).c_str(), &value_, minimum_, maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
}




// Class FloatVSlider
/// Render a vertical float slider and keep the bound attribute in sync.
void FloatVSlider::draw(std::vector<Message> &messageHistory) { 
    ImVec2 size;
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        size.x = 30;
        size.y = (float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f;
    } else {
        size.x = 30;
        size.y = 100;
    }
    
    if (ImGui::VSliderFloat(std::format("##{}", getName()).c_str(),size,&value_, minimum_, maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
 }



// Class FloatDrag
/// Render a float drag control and write the new float value back to the attribute.
void FloatDrag::draw(std::vector<Message> &messageHistory) { 
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragFloat(std::format("##{}", getName()).c_str(),&value_,0.5f, minimum_, maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
 }


//---------------------------------------------------------------------------------------



// Class CharSlider
/// Render a character slider control and synchronize the selected char value.
void CharSlider::draw(std::vector<Message> &messageHistory) {
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::SliderScalar(std::format("##{}" ,getName()).c_str(), attribute_->getDescription()->getDataType() ,&value_, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
}




// Class CharVSlider
/// Render a vertical character slider and keep its bound attribute current.
void CharVSlider::draw(std::vector<Message> &messageHistory) { 
    ImVec2 size;
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        size.x = 30;
        size.y = (float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f;
    } else {
        size.x = 30;
        size.y = 100;
    }
    if (ImGui::VSliderScalar(std::format("##{}" ,getName()).c_str(),ImVec2(20,40),attribute_->getDescription()->getDataType() ,&value_, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
 }



// Class CharDrag
/// Render a drag control for character values and update the bound attribute.
void CharDrag::draw(std::vector<Message> &messageHistory) { 
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragScalar(std::format("##{}" ,getName()).c_str(),attribute_->getDescription()->getDataType(), &value_,1.0f ,&minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
 }

//--------------------------------------------------------------------------------------


// Class LongSlider
/// Render a horizontal long integer slider and save the value to the attribute.
void LongSlider::draw(std::vector<Message> &messageHistory) {
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::SliderScalar(std::format("##{}" ,getName()).c_str(), attribute_->getDescription()->getDataType() ,&value_, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
}




// Class LongVSlider
/// Render a vertical long integer slider and update the attribute value.
void LongVSlider::draw(std::vector<Message> &messageHistory) { 
    ImVec2 size;
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        size.x = 30;
        size.y = (float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f;
    } else {
        size.x = 30;
        size.y = 100;
    }
    if (ImGui::VSliderScalar(std::format("##{}" ,getName()).c_str(),ImVec2(20,40),attribute_->getDescription()->getDataType() ,&value_, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
 }



// Class LongDrag
/// Render a long integer drag control and persist the changed value.
void LongDrag::draw(std::vector<Message> &messageHistory) { 
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragScalar(std::format("##{}" ,getName()).c_str(),attribute_->getDescription()->getDataType(), &value_,1.0f ,&minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
 }

 //--------------------------------------------------------------------------------------


// Class UintSlider
/// Render a horizontal unsigned integer slider and update the attribute value.
void UintSlider::draw(std::vector<Message> &messageHistory) {
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::SliderScalar(std::format("##{}" ,getName()).c_str(), attribute_->getDescription()->getDataType() ,&value_, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
}




// Class UintVSlider
/// Render a vertical unsigned integer slider and keep the bound attribute in sync.
void UintVSlider::draw(std::vector<Message> &messageHistory) { 
    ImVec2 size;
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        size.x = 30;
        size.y = (float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f;
    } else {
        size.x = 30;
        size.y = 100;
    }
    if (ImGui::VSliderScalar(std::format("##{}" ,getName()).c_str(),ImVec2(20,40),attribute_->getDescription()->getDataType() ,&value_, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
 }



// Class UintDrag
/// Render an unsigned integer drag control and write changed values back to the attribute.
void UintDrag::draw(std::vector<Message> &messageHistory) { 
    if (((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) && ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f < maximumWidth_)) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragScalar(std::format("##{}" ,getName()).c_str(),attribute_->getDescription()->getDataType(), &value_,1.0f ,&minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    dimensions_ = ImGui::GetItemRectSize();
    ImGui::PopItemWidth();
 }
