module Vite.Aurora;

namespace Hedron::UI {

///
/// Switches
///

constexpr bool DrawLayoutFrames = false;
constexpr bool EnableWindowDragging = true;

///
/// Containers
///

void Container::Draw() {
    if (Clip) UIRenderer::Clip(Position, Size);
    for (auto &element : GetChildren()) {
        switch (element->Type) {
            // Container
            case ComponentType::Window: {
                if constexpr (EnableWindowDragging) {
                    if (element->Focused) {
                        if (Aurora::sInputState.MouseClicked) Aurora::GetRoot()->MoveToTop(element->ID);
                        if (Aurora::sInputState.Dragging) {
                            element->Offset = Aurora::sInputState.DragCurrentPosition;
                            element->As<Container>()->ComputePosition();

                        } else if (!Aurora::sInputState.Dragging) {
                            element->Position.X += element->Offset.X;
                            element->Position.Y += element->Offset.Y;
                            element->Offset = {};
                            element->As<Container>()->ComputePosition();
                        }
                    }
                }

                auto color = Hedron::Color(0.1f, 0.12f, 0.13f, 1.0f);
                auto position = element->Position;
                position.X += element->Offset.X;
                position.Y += element->Offset.Y;
                UIRenderer::DrawPanel(position, element->Size, color, 8.0f, element->FrameOpacity);
                element->As<Container>()->Draw();

                UIRenderer::End();
                break;
            }
            case ComponentType::ScrollView: {
                //float maxScroll = std::max(0.0f, element->MinSize.Height - element->As<Container>()->Size.Height);
                float maxScroll = std::max(0.0f, element->OriginalSize.Height - element->As<Container>()->Size.Height);
                if (element->Focused) {
                    auto scrollDelta = Input::GetMouseWheelDelta();
                    if (scrollDelta)
                        scrollDelta = 24.0f * scrollDelta;
                    element->Offset.Y = std::clamp(element->Offset.Y + scrollDelta, -maxScroll, 0.0f);
                    //if (scrollDelta) Log("OffsetY: {}, Delta: {}", element->Offset.Y, scrollDelta);
                    element->As<Container>()->ComputePosition();
                }

                auto position = element->Position;
                position.X += element->Size.Width;
                if (maxScroll > 0) {
                    float handleSize = element->Size.Height * (element->Size.Height / element->OriginalSize.Height);
                    float handlePos = std::lerp(0.0f, element->Size.Height - handleSize, element->Offset.Y / maxScroll);
                    position.Y -= handlePos;
                    //UIRenderer::DrawRectangle(position, { 6.0, handlePos }, {});
                    UIRenderer::DrawRectangle(position, { 6.0, handleSize }, Aurora::GetStyle().ColorFrame);
                } else {
                    UIRenderer::DrawRectangle(position, { 6.0f, 16.0f }, {});
                }
                if constexpr (DrawLayoutFrames) {
                    UIRenderer::DrawBorder(1.0f, element->Position, element->Size, Aurora::GetStyle().ColorDebugBorder);
                }
                element->As<Container>()->Draw();
                break;
            }

            case ComponentType::Panel: [[fallthrough]];
            case ComponentType::Container: {
                if constexpr (DrawLayoutFrames) {
                    UIRenderer::DrawBorder(1.0f, element->Position, element->Size, Aurora::GetStyle().ColorDebugBorder);
                }
                element->As<Container>()->Draw();
                break;
            }

            // Controls
            default: {
                element->Draw();
                break;
            }
        }
    }
    if (Clip) {
        UIRenderer::End();
        UIRenderer::Unclip();
    }
}

///
/// Controls
///

void Button::Draw() {
    if (Focused) {
        if (Aurora::sInputState.MouseClicked) if (Click) Click();

        auto &&color = Aurora::sInputState.MousePressed ?
            Aurora::GetStyle().ColorFillPressed :
            Aurora::GetStyle().ColorFillHovered;
        UIRenderer::DrawPanel(Position, Size, color, 0.0f, 1.0f);
    } else {
        auto &&color = Aurora::GetStyle().ColorFillNone;
        UIRenderer::DrawPanel(Position, Size, color, 0.0f, FrameOpacity);
    }

    if constexpr (DrawLayoutFrames) {
        UIRenderer::DrawBorder(1.0f, Position, Size, Aurora::GetStyle().ColorDebugBorder);
    }

    Position2D position = {
        (Position.X + 8.0f + (Size.Width - MinSize.Width) * Alignment.X),
        (Position.Y + 4.0f + (Size.Height) * Alignment.Y),
    };
    UIRenderer::DrawText(position, Text, Color, Font);
}

void CheckBox::Draw() {
    if (Focused) {
        if (Aurora::sInputState.MouseClicked) Value = !Value;

        auto &&color = Aurora::GetStyle().ColorFocusUnderline;
        UIRenderer::DrawRectangle(Position, Size, color);
    }

    if constexpr (DrawLayoutFrames) {
        UIRenderer::DrawBorder(1.0f, Position, Size, Aurora::GetStyle().ColorDebugBorder);
    }

    // CheckBox Label
    Position2D position = { Position.X + 8.0f, (Position.Y + MinSize.Height / 2 + 4.0f) };
    UIRenderer::DrawText(position, Text, Color, Font);

    // CheckBox Outer Rectangle
    position.X = Position.X + Size.Width - OutherSize.Width - 4.0f;
    position.Y -= 12.0f;
    UIRenderer::DrawRectangle(position, OutherSize, OutherColor);

    // CheckBox Inner Rectangle
    position.X += 3.0f;
    position.Y += 3.0f;
    if (Value) {
        UIRenderer::DrawRectangle(position, InnerSize, InnerColor);
    } else {
        UIRenderer::DrawRectangle(position, InnerSize, {});
    }
}

void InputBox::Draw() {
    if (Focused) {
        if (Aurora::sInputState.MouseClicked) Active = !Active;
    }

    auto &&bgColor = Active ? Focused ? Aurora::GetStyle().ColorFocusUnderline : Aurora::GetStyle().ColorFocusUnderlineActive : Aurora::GetStyle().ColorFillNone;
    UIRenderer::DrawPanel(Position, Size, bgColor, 0.0f, FrameOpacity);

    static bool once = true;
    if (Active && once) {
        Text += "Yeah";
        once = false;
    }

    if constexpr (DrawLayoutFrames) {
        UIRenderer::DrawBorder(1.0f, Position, Size, Aurora::GetStyle().ColorDebugBorder);
    }

    Position2D textPos = {
        Position.X + 8.0f,
        Position.Y + MinSize.Height / 2 + 4.0f,
    };
    UIRenderer::DrawText(textPos, Text, Color, Font);

    if (Active) {
        // TextWidth...
        //UIRenderer::DrawLine({ Position.X +textWidth, Position.Y }, { Position.X, Position.Y + Size.Height}, Aurora::GetStyle().ColorFillHovered);
    }
}

void Image::Draw() {
    UIRenderer::DrawImage(Position, Size, Data);
}

void Label::Draw() {
    if constexpr (DrawLayoutFrames) {
        UIRenderer::DrawBorder(1.0f, Position, Size, Aurora::GetStyle().ColorDebugBorder);
    }

    Position2D position = { Position.X, Position.Y + MinSize.Height };
    UIRenderer::DrawText(position, Text, Color, Font);
}

void Selection::Draw() {
    // Draw the selection area
    if (Focused) {
        if (Aurora::sInputState.MouseClicked) if (Click) Click();

        auto &&color = Aurora::sInputState.MousePressed ?
            Aurora::GetStyle().ColorFillPressed :
            Aurora::GetStyle().ColorFillHovered;
        UIRenderer::DrawPanel(Position, Size, color, 0.0f, 1.0f);
    } else {
        auto &&color = Aurora::GetStyle().ColorFillNone;
        UIRenderer::DrawPanel(Position, Size, color, 0.0f, FrameOpacity);
    }
    auto bgColor = Hedron::Color(0.15f, 0.15f, 0.15f, 1.0f);

    // Draw the currently selected option
    const Position2D textPos = {
        Position.X + 8.0f,
        Position.Y + Size.Height / 2 + 4.0f,
    };
    UIRenderer::DrawText(textPos, Text, Color, Font);
    //UIRenderer::DrawText(textPos, Options[SelectedIndex], Color(1.0f, 1.0f, 1.0f, 1.0f), nullptr);

    // Simulate dropdown functionality
    auto buttonPosition = Position2D(Size.Width, 0.0f);
    auto positionX = Position.X + buttonPosition.X;
    auto positionY = Position.Y + buttonPosition.Y;
    UIRenderer::DrawPanel({ positionX, positionY }, { 20.0f, Size.Height }, bgColor, 0.0f, FrameOpacity);
    //, "▼"
    /*if (U) {
        ShowDropdown = !ShowDropdown;
    }*/

    // Draw dropdown options if open
    if (ShowDropdown) {
        DrawDropdown();
    }
}

void Selection::DrawDropdown() {
    // Draw the dropdown options
    //const float optionHeight = 25.0f;
    //for (size_t i = 0; i < Options.size(); ++i) {
    //    const Position optionPos = {
    //        Position.X,
    //        Position.Y + Size.Height + optionHeight * static_cast<float>(i),
    //    };
    //    const bool selected = (i == SelectedIndex);
    //    //const bool clicked = UIRenderer::DrawButton(optionPos, { Size.Width, optionHeight }, Options[i], selected);
    //    if (clicked) {
    //        SelectedIndex = i;
    //        ShowDropdown = false;
    //    }
    //}
}

void Seperator::Draw() {
    // ToDo: Check also line shader "vertex/ui" "fragment/ui/line"
    // ToDo: Additive BlendMode
    //const float padding = 64.0f;
    //float minX = std::min(native->Start.X, native->Stop.X) - padding;
    //float minY = std::min(native->Start.Y, native->Stop.Y) - padding;
    //float maxX = std::max(native->Start.X, native->Stop.X) + padding;
    //float maxY = std::max(native->Start.Y, native->Stop.Y) + padding;
    //float width = maxX - minX;
    //float height = maxY - minY;
    // UIRenderer::Line(e->Start, e->Stop, e->Color);
}

void Slider::Draw() {
    // Track
    const Hedron::Color trackColor = Hedron::Color(0.2f, 0.2f, 0.2f, 1.0f);
    UIRenderer::DrawRectangle(Position, Size, trackColor);

    if constexpr (DrawLayoutFrames) {
        UIRenderer::DrawBorder(1.0f, Position, Size, Aurora::GetStyle().ColorDebugBorder);
    }

    const Position2D handlePosition = {
        Position.X + (Size.Width - HandleWidth) * Value,
        Position.Y
    };

    // Handle
    if (Focused && Aurora::sInputState.MousePressed) {
        if (Aurora::sInputState.MousePressed) {
            const float newHandleX = Aurora::sInputState.LastMousePosition.X - DragOffset;
            Value = std::clamp((newHandleX - Position.X) / (Size.Width - HandleWidth), 0.0f, 1.0f);
        }

        auto &&color = Aurora::GetStyle().ColorPrimary;
        UIRenderer::DrawRectangle(handlePosition, { HandleWidth, Size.Height }, color);

    } else {
        auto &&color = Aurora::GetStyle().ColorFrame;
        UIRenderer::DrawRectangle(handlePosition, { HandleWidth, Size.Height }, color);
    }
}

///
/// ToDo
///

void ColorPicker::Draw() {
    // Implement the drawing of the color picker
    auto hovered = Hovered(Aurora::sInputState.LastMousePosition);

    // Draw the color picker area
    const auto bgColor = Hedron::Color(0.1f, 0.1f, 0.1f, 1.0f);
    UIRenderer::DrawPanel(Position, Size, bgColor, 0.0f, FrameOpacity);

    // Simulate color spectrum representation
    for (float y = 0.0f; y < Size.Height; y++) {
        for (float x = 0.0f; x < Size.Width; x++) {
            float r = x / Size.Width;
            float g = y / Size.Height;
            float b = 0.5f; // Fixed blue value for simplicity
            Hedron::Color color(r, g, b, 1.0f);
            Position2D pixelPos = {
                Position.X + x,
                Position.Y + y,
            };
            //UIRenderer::DrawPixel(pixelPos, color);
        }
    }

    // Draw selected color
    Position2D selectedColorPos = {
        Position.X + Size.Width + 8.0f,
        Position.Y + Size.Height / 2,
    };
    Hedron::Color selectedColor(1.0f, 1.0f, 1.0f, 1.0f); // Simulated selected color
    UIRenderer::DrawPanel(selectedColorPos, { 30.0f, 30.0f }, selectedColor, 0.0f, 1.0f);
}

void Table::DrawHeader() {
    //const Position textPos = {
    //    Position.X,
    //    Position.Y + RowHeight / 2,
    //};
    //for (size_t i = 0; i < Header.size(); ++i) {
    //    UIRenderer::DrawText(textPos + Position(ColumnWidths[i] / 2, 0), Header[i], Color(1.0f, 1.0f, 1.0f, 1.0f), nullptr);
    //    textPos.X += ColumnWidths[i];
    //}
}

void Table::DrawRows() {
    //Position textPos = {
    //    Position.X,
    //    Position.Y + RowHeight,
    //};
    //for (const auto &row : Data) {
    //    for (size_t i = 0; i < row.size(); ++i) {
    //        UIRenderer::DrawText(textPos + Position(ColumnWidths[i] / 2, 0), row[i], Color(1.0f, 1.0f, 1.0f, 1.0f), nullptr);
    //        textPos.X += ColumnWidths[i];
    //    }
    //    textPos.X = Position.X;
    //    textPos.Y += RowHeight;
    //}
}

void Tree::Draw() {
    // Implement the drawing of the tree
    auto hovered = Hovered(Aurora::sInputState.LastMousePosition);

    // Draw the tree area
    const auto bgColor = Hedron::Color(0.15f, 0.15f, 0.15f, 1.0f);
    UIRenderer::DrawPanel(Position, Size, bgColor, 0.0f, FrameOpacity);

    // Simulate tree nodes
    DrawTreeNode({ Position.X + 20.0f, Position.Y + 20.0f }, "Node 1");
    DrawTreeNode({ Position.X + 20.0f, Position.Y + 60.0f }, "Node 2");
    DrawTreeNode({ Position.X + 40.0f, Position.Y + 100.0f }, "Node 2.1");
    DrawTreeNode({ Position.X + 40.0f, Position.Y + 140.0f }, "Node 2.2");
}

void Tree::DrawTreeNode([[maybe_unused]] const Position2D &position, const string_view &text) {
    if (text.empty()) return;
    //// Draw a tree node with expand/collapse functionality
    //auto hovered = Hovered(Aurora::sLastMousePosition);
    //const float nodeWidth = 20.0f;
    //const float nodeHeight = 20.0f;
    //const float textIndent = 25.0f;
    //bool expanded = true; // Simulated node expansion state

    //// Draw expand/collapse button
    //const Position buttonPos = {
    //    position.X - 5.0f,
    //    position.Y + nodeHeight / 2,
    //};
    //if (UIRenderer::DrawButton(buttonPos, { 15.0f, 15.0f }, expanded)) {
    //    expanded = !expanded;
    //}

    //// Draw node text
    //const Position textPos = {
    //    position.X + textIndent,
    //    position.Y + nodeHeight / 2,
    //};
    //UIRenderer::DrawText(textPos, text, Color(1.0f, 1.0f, 1.0f, 1.0f), nullptr);

    //// Draw child nodes if expanded
    //if (expanded) {
    //    DrawTreeNode({ position.X, position.Y + 30.0f }, "Child Node 1");
    //    DrawTreeNode({ position.X, position.Y + 60.0f }, "Child Node 2");
    //}
}

}
