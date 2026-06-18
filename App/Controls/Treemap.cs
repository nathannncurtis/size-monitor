using System.Windows.Controls;

namespace SizeMonitor.Controls;

public class Treemap : Panel
{
    protected override System.Windows.Size MeasureOverride(System.Windows.Size availableSize)
        => availableSize;

    protected override System.Windows.Size ArrangeOverride(System.Windows.Size finalSize)
        => finalSize;
}
