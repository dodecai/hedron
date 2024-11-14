export module Vite.Aurora.Control.Table;

import Vite.Core;
import Vite.Renderer.Texture;
import Vite.Aurora.Control;

export namespace Hedron::UI {

class Table: public Control {
public:
    Table(const string &id): Control(id, ComponentType::Table) {
        ColumnWidths = { 100.0f, 150.0f, 200.0f };
        RowHeight = 30.0f;
        Header = { "Column 1", "Column 2", "Column 3" };
        Data = {
            { "Row 1 Data 1", "Row 1 Data 2", "Row 1 Data 3" },
            { "Row 2 Data 1", "Row 2 Data 2", "Row 2 Data 3" },
        };
    }
    ~Table() = default;

    void Draw() override {
        DrawHeader();
        DrawRows();
    }

private:
    void DrawHeader();
    void DrawRows();

private:
    std::vector<float> ColumnWidths;
    float RowHeight;
    std::vector<string> Header;
    std::vector<std::vector<string>> Data;
};

}
