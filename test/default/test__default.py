from pathlib import Path
from spl_core.test_utils.base_variant_test_runner import BaseVariantTestRunner


class Test_default(BaseVariantTestRunner):
    @property
    def component_paths(self):
        return [
            Path("components/calc"),
            Path("components/a"),
            Path("components/moving_average"),
            Path("components/diagnostic"),
            Path("components/led"),
            Path("components/voltage_converter"),
            Path("components/voltage_monitor"),
            Path("components/power_manager"),
            Path("components/position_manager"),
        ]

    @property
    def expected_build_artifacts(self):
        return []

    def test_build(self):
        pass

    def test_reports(self):
        pass
